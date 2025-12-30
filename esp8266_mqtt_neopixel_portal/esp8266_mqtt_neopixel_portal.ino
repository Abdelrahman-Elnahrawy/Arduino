/*
 * Project: ESP8266 MQTT & NeoPixel Configuration Portal
 * Author: Abdelrahman Elnahrawy
 * Description: An IoT node that uses a Captive Portal to save WiFi/MQTT 
 * credentials to EEPROM, controls NeoPixels, and communicates via MQTT.
 */

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>

// --- Configuration & Pinout ---
#define NEOPIXEL_PIN    14    // D5 on NodeMCU
#define NUM_PIXELS      30
#define BRIGHTNESS      50
#define HOTSPOT_MODE    0
#define NORMAL_MODE     1

// --- Global Objects ---
Adafruit_NeoPixel strip(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
ESP8266WebServer server(80);

// --- State Variables ---
char storedSSID[32], storedPassword[32], storedBroker[32];
const char* sub_Topic = "nosa";
const char* pub_Topic = "IR_RAW_DATA_TOPIC";
unsigned long lastMsg = 0;
unsigned long LostConnectionTimer;
bool CurrentMode;
int value = 0;

// ================================================================
//                         WIFI & PORTAL
// ================================================================

void startAccessPoint(const char* AP_NAME) {
    CurrentMode = HOTSPOT_MODE;
    LostConnectionTimer = millis(); 
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_NAME);
    
    Serial.print("Hotspot Active: ");
    Serial.println(WiFi.softAPIP());

    server.on("/", handleRoot);
    server.on("/save", handleSave);
    server.begin();
}

void handleRoot() {
    // Professional CSS-styled interface
    String html = "<html><head><meta charset='UTF-8'><title>Config</title>";
    html += "<style>body{display:flex;justify-content:center;align-items:center;height:100vh;background:#f2f2f2;font-family:Arial;}";
    html += ".container{width:80%;padding:20px;background:#fff;border-radius:8px;box-shadow:0 2px 4px rgba(0,0,0,0.2);}";
    html += "input{width:100%;padding:10px;margin:10px 0;border-radius:20px;border:1px solid #ccc;}";
    html += "button{width:100%;padding:10px;background:#4CAF50;color:#fff;border:none;border-radius:10px;cursor:pointer;}</style></head>";
    html += "<body><div class='container'><h1>Unimote Config</h1>";
    html += "<form method='POST' action='/save'>";
    html += "<input type='text' name='wifi-ssid' placeholder='WiFi SSID'>";
    html += "<input type='password' name='wifi-password' placeholder='Password'>";
    html += "<input type='text' name='mqtt-broker' placeholder='MQTT Broker IP (e.g. 192.168.1.50)'>";
    html += "<button type='submit'>Save & Restart</button></form></div></body></html>";
    server.send(200, "text/html", html);
}

void handleSave() {
    String s = server.arg("wifi-ssid");
    String p = server.arg("wifi-password");
    String m = server.arg("mqtt-broker");

    // Write to EEPROM
    for (int i = 0; i < 32; ++i) EEPROM.write(i, (i < s.length()) ? s[i] : '\0');
    for (int i = 0; i < 32; ++i) EEPROM.write(i + 32, (i < p.length()) ? p[i] : '\0');
    for (int i = 0; i < 32; ++i) EEPROM.write(i + 64, (i < m.length()) ? m[i] : '\0');
    
    EEPROM.commit();
    server.send(200, "text/html", "<h1>Saved! Restarting...</h1>");
    delay(2000);
    ESP.restart();
}

void connectToWiFi() {
    unsigned long startAttempt = millis();
    WiFi.mode(WIFI_STA);
    WiFi.begin(storedSSID, storedPassword);

    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        if (millis() - startAttempt > 10000) { // 10s timeout
            Serial.println("\nWiFi Failed -> AP Mode");
            startAccessPoint("Unimote Config");
            return;
        }
    }
    Serial.println("\nConnected! IP: " + WiFi.localIP().toString());
}

// ================================================================
//                             MQTT
// ================================================================

void handleMQTTMessage(char* topic, byte* payload, unsigned int length) {
    if (strcmp(topic, sub_Topic) == 0) {
        Serial.println("IR Payload Received");
        // Logic for handling IR pulses goes here
    }
}

void connectToMQTT() {
    mqttClient.setServer(storedBroker, 1883);
    mqttClient.setCallback(handleMQTTMessage);

    if (mqttClient.connect("ESP8266_Unimote")) {
        Serial.println("MQTT Connected");
        mqttClient.publish(pub_Topic, "Node Online");
        mqttClient.subscribe(sub_Topic);
    }
}

// ================================================================
//                           MAIN SYSTEM
// ================================================================

void setup() {
    Serial.begin(115200);
    EEPROM.begin(200);
    
    strip.begin();
    strip.setBrightness(BRIGHTNESS);
    strip.show();

    // Load data from EEPROM
    for (int i = 0; i < 32; ++i) {
        storedSSID[i] = EEPROM.read(i);
        storedPassword[i] = EEPROM.read(i + 32);
        storedBroker[i] = EEPROM.read(i + 64);
    }

    if (strlen(storedSSID) > 1) {
        CurrentMode = NORMAL_MODE;
        connectToWiFi();
        if (WiFi.status() == WL_CONNECTED) connectToMQTT();
    } else {
        startAccessPoint("Unimote Setup");
    }
}

void loop() {
    if (CurrentMode == HOTSPOT_MODE) {
        server.handleClient();
        // Auto-restart if left in hotspot mode for 3 minutes
        if (millis() - LostConnectionTimer > 180000) ESP.restart();
    } else {
        // Normal Mode Logic
        if (WiFi.status() != WL_CONNECTED) {
            connectToWiFi();
        } else if (!mqttClient.connected()) {
            connectToMQTT();
        } else {
            mqttClient.loop();
            
            // Periodic Heartbeat
            if (millis() - lastMsg > 5000) {
                lastMsg = millis();
                mqttClient.publish(pub_Topic, "Heartbeat");
            }
        }
    }
}