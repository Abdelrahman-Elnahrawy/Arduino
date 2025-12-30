/*
 * File Name   : esp8266_mqtt_neopixel_multi_led_controller.ino
 * Description : Control multiple NeoPixel LEDs using ESP8266 via MQTT.
 * Author      : Abdelrahman Seelim
 * Platform    : ESP8266 + Arduino IDE
 */

#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <PubSubClient.h>

/* ===================== WiFi Credentials ===================== */
const char* ssid     = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

/* ===================== MQTT Configuration =================== */
const char* mqtt_server     = "mqtt_server_ip";
const char* mqtt_username   = "mqtt_username";
const char* mqtt_password   = "mqtt_password";
const char* mqtt_client_id  = "mqtt_client_id";

/* ===================== NeoPixel Configuration =============== */
#define NEOPIXEL_PIN   11
#define NUM_LEDS       30

Adafruit_NeoPixel neopixels(
  NUM_LEDS,
  NEOPIXEL_PIN,
  NEO_GRB + NEO_KHZ800
);

/* ===================== MQTT Topics ========================== */
const char* topic_brightness    = "neopixel/brightness";
const char* topic_color_prefix  = "neopixel/color/";

/* ===================== LED State Storage ==================== */
int brightness[NUM_LEDS];        // Brightness per LED (0–255)
uint32_t colors[NUM_LEDS];       // RGB color per LED

/* ===================== MQTT Client ========================== */
WiFiClient espClient;
PubSubClient mqttClient(espClient);

/* ===================== WiFi Connection ====================== */
void setup_wifi() {
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

/* ===================== MQTT Callback ======================== */
void callback(char* topic, byte* payload, unsigned int length) {

  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(message);

  /* -------- Brightness Control -------- */
  if (strcmp(topic, topic_brightness) == 0) {

    int value = message.toInt();
    value = constrain(value, 0, 255);

    neopixels.setBrightness(value);
    neopixels.show();
  }

  /* -------- Color Control Per LED ----- */
  else if (strncmp(topic, topic_color_prefix,
                   strlen(topic_color_prefix)) == 0) {

    int led_index = atoi(topic + strlen(topic_color_prefix));
    if (led_index >= 0 && led_index < NUM_LEDS) {

      int r, g, b;
      sscanf(message.c_str(), "%d,%d,%d", &r, &g, &b);

      colors[led_index] = neopixels.Color(r, g, b);
      neopixels.setPixelColor(led_index, colors[led_index]);
      neopixels.show();
    }
  }
}

/* ===================== MQTT Reconnect ======================= */
void reconnect() {
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT...");

    if (mqttClient.connect(
          mqtt_client_id,
          mqtt_username,
          mqtt_password)) {

      Serial.println("Connected");

      mqttClient.subscribe(topic_brightness);

      for (int i = 0; i < NUM_LEDS; i++) {
        char topic[40];
        sprintf(topic, "neopixel/color/%d", i);
        mqttClient.subscribe(topic);
      }

    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      delay(5000);
    }
  }
}

/* ===================== Setup ================================ */
void setup() {
  Serial.begin(115200);

  setup_wifi();

  neopixels.begin();
  neopixels.clear();
  neopixels.show();

  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(callback);
}

/* ===================== Loop ================================ */
void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
}
