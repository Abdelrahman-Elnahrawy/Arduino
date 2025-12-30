#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Replace with your WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Replace with your MQTT broker details
const char* mqttServer = "MQTT_BROKER_IP";
const int mqttPort = 1883;
const char* mqttUser = "MQTT_USERNAME";
const char* mqttPassword = "MQTT_PASSWORD";
const char* mqttTopic = "IR_RAW_DATA_TOPIC";

// IR LED connection pin
const uint16_t irLedPin = 1; // Connect IR LED to GPIO1

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
IRsend irSender(irLedPin);

// Connect to WiFi network
void connectToWiFi() {
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

// Connect to MQTT broker and subscribe to topic
void connectToMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(handleMQTTMessage);
  
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");
    
    if (mqttClient.connect("ESP8266Client", mqttUser, mqttPassword)) {
      Serial.println("MQTT connected");
      mqttClient.subscribe(mqttTopic);
    }
    else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

// Callback function to handle incoming MQTT messages
void handleMQTTMessage(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, mqttTopic) == 0) {
    Serial.println("Received IR raw data");
    
    // Transmit the IR raw data
    for (unsigned int i = 0; i < length; i++) {
      irSender.sendRaw(payload[i], 32, kHz); // 38kHz typical IR carrier
      delay(50); // Adjust delay for timing
    }
    
    Serial.println("IR raw data transmitted");
  }
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();    // Connect ESP8266 to WiFi
  connectToMQTT();    // Connect ESP8266 to MQTT broker
}

void loop() {
  if (!mqttClient.connected()) {
    connectToMQTT(); // Reconnect if disconnected
  }
  
  mqttClient.loop();  // Process incoming MQTT messages
}