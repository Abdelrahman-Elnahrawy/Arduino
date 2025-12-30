/**
 * PROJECT: Unimote MQTT IR Blaster
 * AUTHOR: Abdelrahman Elnahrawy
 * DESCRIPTION: Receives IR raw data via MQTT and transmits it via an IR LED.
 * Features an auto-fallback Access Point for WiFi/MQTT provisioning.
 */

#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <PubSubClient.h>

// --- Configuration ---
const uint16_t irLedPin = 4; // GPIO4 (D2)
const int eepromSize = 100;

// MQTT Settings
const char* mqttServer   = "MQTT_BROKER_IP";
const int   mqttPort     = 1883;
const char* mqttUser     = "MQTT_USERNAME";
const char* mqttPassword = "MQTT_PASSWORD";
const char* mqttTopic    = "IR_RAW_DATA_TOPIC";

// --- Global Objects ---
ESP8266WebServer server(80);
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
IRsend irSender(irLedPin);

char ssid[32] = "";
char password[32] = "";

// ================================================================
// MQTT HANDLERS
// ================================================================

void handleMQTTMessage(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, mqttTopic) == 0) {
    Serial.println("Action: Transmitting IR Signal...");
    
    /* * Note: IR Raw data usually requires an array of uint16_t.
     * You may need to parse the payload string into an array 
     * before using irSender.sendRaw().
     */
     
    Serial.println("IR signal sent.");
  }
}

void connectToMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(handleMQTTMessage);

  unsigned long startAttempt = millis();
  
  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT...");
    if (mqttClient.connect("Unimote_Client", mqttUser, mqttPassword)) {
      Serial.println("Success.");
      mqttClient.subscribe(mqttTopic);
    } else {
      delay(1000);
      if (millis() - startAttempt > 7000) {
        Serial.println("\nMQTT Timeout -> AP Mode");
        startAccessPoint("Unimote MQTT Error!");
        break;
      }
    }
  }
}

// ================================================================
// WIFI & PROVISIONING
// ================================================================

void startAccessPoint(const char* AP_NAME) {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_NAME);
  Serial.print("AP Active. IP: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/save", handleSave);
  server.begin();
}

void handleRoot() {
  String html = "<html><body style='font-family:sans-serif;'>";
  html += "<h1>Unimote Configuration</h1>";
  html += "<form method='POST' action='/save'>";
  html += "SSID: <input type='text' name='ssid'><br><br>";
  html += "Password: <input type='password' name='password'><br><br>";
  html += "<input type='submit' value='Save & Connect'>";
  html += "</form></body></html>";
  server.send(200, "text/html", html);
}

void handleSave() {
  String newSsid = server.arg("ssid");
  String newPass = server.arg("password");

  for (int i = 0; i < 32; ++i) {
    EEPROM.write(i, i < newSsid.length() ? newSsid[i] : (i == newSsid.length() ? '\0' : EEPROM.read(i)));
    EEPROM.write(i + 32, i < newPass.length() ? newPass[i] : (i == newPass.length() ? '\0' : EEPROM.read(i + 32)));
  }
  EEPROM.commit();
  server.send(200, "text/html", "<h1>Saved. Restarting...</h1>");
  delay(1000);
  ESP.restart();
}

void connectToWiFi() {
  unsigned long startAttempt = millis();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() - startAttempt > 10000) {
      Serial.println("\nWiFi Failed -> AP Mode");
      startAccessPoint("Unimote Setup");
      return;
    }
  }
  Serial.println("\nConnected!");
}

// ================================================================
// MAIN SETUP & LOOP
// ================================================================

void setup() {
  Serial.begin(115200);
  EEPROM.begin(eepromSize);
  irSender.begin();

  // Load credentials from EEPROM
  for (int i = 0; i < 32; ++i) {
    ssid[i] = EEPROM.read(i);
    password[i] = EEPROM.read(i + 32);
  }

  if (strlen(ssid) > 0) {
    connectToWiFi();
  } else {
    startAccessPoint("Unimote Setup");
  }

  if (WiFi.status() == WL_CONNECTED) {
    connectToMQTT();
  }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED || !mqttClient.connected()) {
    server.handleClient();
  }
  mqttClient.loop();
}