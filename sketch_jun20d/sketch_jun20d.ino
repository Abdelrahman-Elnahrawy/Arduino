#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

// MQTT broker details
const char* mqtt_server = "mqtt_server_ip";
const char* mqtt_username = "mqtt_username";
const char* mqtt_password = "mqtt_password";
const char* mqtt_client_id = "mqtt_client_id";

// NeoPixel settings
const int num_leds = 30;  // Number of NeoPixel LEDs
const int pin_neopixel = 11;  // Pin connected to the NeoPixel data input
Adafruit_NeoPixel neopixels(num_leds, pin_neopixel, NEO_GRB + NEO_KHZ800);

// MQTT topics
const char* base_topic = "neopixel/";
const char* topic_brightness = "neopixel/brightness";
const char* topic_color_prefix = "neopixel/color/";

// Brightness values for each LED (0-255)
int brightness[num_leds] ;

// Color values for each LED
uint32_t colors[num_leds] = {neopixels.Color(255, 0, 0),  // Red
                             neopixels.Color(0, 255, 0),  // Green
                             neopixels.Color(0, 0, 255),  // Blue
                             neopixels.Color(255, 255, 0),  // Yellow
                             neopixels.Color(255, 255, 255)};  // White

// MQTT client instance
WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String payloadStr = "";
  for (int i = 0; i < length; i++) {
    payloadStr += (char)payload[i];
  }

  Serial.print("Received message from topic: ");
  Serial.println(topic);
  Serial.print("Payload: ");
  Serial.println(payloadStr);

  if (strcmp(topic, topic_brightness) == 0) {
    // Parse brightness value from payload
    int ledIndex = payloadStr.toInt();
    if (ledIndex >= 0 && ledIndex < num_leds) {
      brightness[ledIndex] = payloadStr.toInt();
      if (brightness[ledIndex] < 0) {
        brightness[ledIndex] = 0;
      } else if (brightness[ledIndex] > 255) {
        brightness[ledIndex] = 255;
      }
      neopixels.setBrightness(brightness[ledIndex]);
      neopixels.show();
    }
  } else if (strncmp(topic, topic_color_prefix, strlen(topic_color_prefix)) == 0) {
    // Extract LED index from topic
    int ledIndex = atoi(topic + strlen(topic_color_prefix));
    if (ledIndex >= 0 && ledIndex < num_leds) {
      // Parse color values from payload (expecting R,G,B format)
      int comma1 = payloadStr.indexOf(',');
      int comma2 = payloadStr.lastIndexOf(',');
      int r = payloadStr.substring(0, comma1).toInt();
      int g = payloadStr.substring(comma1 + 1, comma2).toInt();
      int b = payloadStr.substring(comma2 + 1).toInt();
      colors[ledIndex] = neopixels.Color(r, g, b);
      neopixels.setPixelColor(ledIndex, colors[ledIndex]);
      neopixels.show();
    }
  }
}

void reconnect() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqttClient.connect(mqtt_client_id, mqtt_username, mqtt_password)) {
      Serial.println("connected");
      mqttClient.subscribe(topic_brightness);
      for (int i = 0; i < num_leds; i++) {
        char topic_color[50];
        sprintf(topic_color, "%s%d/color", base_topic, i);
        mqttClient.subscribe(topic_color);
      }
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  neopixels.begin();
  for (int i = 0; i < num_leds; i++) {
    neopixels.setPixelColor(i, colors[i]);
  }
  neopixels.show();
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(callback);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
}
