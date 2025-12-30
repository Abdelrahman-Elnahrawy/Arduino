/*
 * Project: ESP8266 Smart Hub with NeoPixel & Relay Control
 * Author: Abdelrahman Elnahrawy
 * Features: 
 * - 5 Relay Channels + 1 PWM Dimmer
 * - WS2812B NeoPixel Strip (30 pixels)
 * - MQTT Remote Control & Web Configuration
 * - Motion Sensing Auto-Lighting
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>

// --- NeoPixel Configuration ---
#define LED_PIN    2   // GPIO2 (D4)
#define LED_COUNT  30
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// --- Global Variables & Pins ---
ESP8266WebServer server(80);
WiFiClient espClient;
PubSubClient client(espClient);

int relayPins[] = {4, 5, 0, 15, 16}; // R1 to R5
int motionSensor = 3;
int buttonPins[] = {14, 12, 13};     // KP_1, KP_2, KP_3

// ... (WiFi and MQTT setup logic remains consistent with previous modules) ...

/**
 * callback: Processes incoming MQTT messages for Relays and Lighting
 */
void callback(char* topic, byte* payload, unsigned int length) {
  // Logic to parse payload and toggle relayPins[0-4]
  // Also logic to trigger NeoPixel animations based on MQTT data
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  
  // Initialize NeoPixels
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'

  // Initialize Relays
  for(int i=0; i<5; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], EEPROM.read(101 + i));
  }

  setup_wifi();
  client.setServer("192.168.1.123", 1883);
  client.setCallback(callback);
}

void loop() {
  // Simple visual feedback: constant Red wipe (Note: Non-blocking code is better here)
  colorWipe(strip.Color(255, 0, 0), 50);

  server.handleClient();
  if (!client.connected()) reconnect();
  client.loop();

  // Handle Motion Sensor and Logic Modes (LM)
  // LM 0: Manual, LM 1: Sensor Auto, LM 2: Timer Auto
}

/**
 * Fills the dots one after the other with a color
 */
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}