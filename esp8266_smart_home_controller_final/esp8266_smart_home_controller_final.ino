/*
 * Project: ESP8266 6-Channel IoT Relay Controller
 * Author: Abdelrahman Elnahrawy
 * Features: 
 * - MQTT Remote Control (HiveMQ / Local Broker)
 * - Captive Portal for WiFi & Device Setup
 * - Motion Sensor (PIR) with Auto-Timer Modes
 * - 6th Channel Dimmer (PWM)
 * - EEPROM State Recovery
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// --- Configuration ---
const char* mqtt_server = "broker.mqtt-dashboard.com";
#define MSG_BUFFER_SIZE (100)

// --- Pin Map ---
int relayPins[] = {4, 5, 0, 2, 15, 16}; // R1-R6 (R6 is PWM)
int PIR_PIN     = 3;  // Motion Sensor
int KEY_PINS[]  = {14, 12, 13}; // Physical Buttons

// --- Logic Variables ---
bool relayStates[5];
int  pwmValue = 0;
int  logicMode = 3; // 1: Sensor, 2: Timer, 3: Manual
unsigned long relayDelay = 10000;

WiFiClient espClient;
PubSubClient client(espClient);
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);

  // Initialize Pins
  for(int i=0; i<5; i++) {
    pinMode(relayPins[i], OUTPUT);
    relayStates[i] = EEPROM.read(101 + i);
    digitalWrite(relayPins[i], relayStates[i]);
  }
  pinMode(relayPins[5], OUTPUT); // PWM Channel
  pinMode(PIR_PIN, INPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  server.handleClient();
  if (!client.connected() && WiFi.status() == WL_CONNECTED) reconnect();
  client.loop();

  handleAutomation();
  handlePhysicalButtons();
}

/**
 * Automates Relay 1 based on Motion Sensor & Logic Mode
 */
void handleAutomation() {
  bool motionDetected = digitalRead(PIR_PIN);
  
  if (logicMode == 1) { // Sensor Mode
    digitalWrite(relayPins[0], motionDetected);
  } 
  else if (logicMode == 2) { // Timer Mode
    static unsigned long timerStart = 0;
    if (motionDetected) {
      timerStart = millis();
      digitalWrite(relayPins[0], HIGH);
    }
    if (millis() - timerStart > relayDelay) {
      digitalWrite(relayPins[0], LOW);
    }
  }
}