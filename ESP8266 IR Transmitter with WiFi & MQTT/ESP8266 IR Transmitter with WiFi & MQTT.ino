#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <PubSubClient.h>


// IR LED connection pin
const uint16_t irLedPin = 4;

//wifi
const char* ssid = "";      // Initialize SSID
const char* password = "";  // Initialize password
const int eepromSize = 100;  // Size of EEPROM to store username and password

//mqtt
const char* mqttServer = "MQTT_BROKER_IP";
const int mqttPort = 1883;
const char* mqttUser = "MQTT_USERNAME";
const char* mqttPassword = "MQTT_PASSWORD";
const char* mqttTopic = "IR_RAW_DATA_TOPIC";



ESP8266WebServer server(80);

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

IRsend irSender(irLedPin);// intialize IR library with specified pin



void connectToMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(handleMQTTMessage);

  unsigned long MQTT_Connection_TIMER = millis();
  
  while (!mqttClient.connected()) {

    Serial.println("Connecting to MQTT...");
  
    if (mqttClient.connect("ESP8266Client", mqttUser, mqttPassword)) {
      Serial.println("MQTT connected");
      mqttClient.subscribe(mqttTopic);
    }
    else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 1 seconds...");
      delay(1000);
    }
       if(millis()-MQTT_Connection_TIMER>7000){
             Serial.println("failed to connect to mqtt --> starting hotspot");
      startAccessPoint("Unimote MQTT !");
      break;
      }
  }
    
  }
void handleMQTTMessage(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, mqttTopic) == 0) {
    Serial.println("Received IR raw data");
    
    // Transmit the IR raw data
    for (unsigned int i = 0; i < length; i++) {
      //irSender.sendRaw(payload[i], 32, kHz);
      delay(50); // Adjust delay as needed
    }
    
    Serial.println("IR raw data transmitted");
  }
}
void setup() {
  Serial.begin(115200);
  EEPROM.begin(eepromSize);

  // Read stored username and password from EEPROM
  char storedSSID[32];
  char storedPassword[32];
  for (int i = 0; i < 32; ++i) {
    storedSSID[i] = EEPROM.read(i);
    storedPassword[i] = EEPROM.read(i + 32);
  }

  // Check if stored credentials are available
  if (strlen(storedSSID) > 0 && strlen(storedPassword) > 0) {
    ssid = storedSSID;
    password = storedPassword;
    connectToWiFi();
  } else {
    startAccessPoint("Unimote Credentials !");
  }
  
  if(WiFi.status() == WL_CONNECTED){
  connectToMQTT();}
}

void loop() {
    if(WiFi.status() != WL_CONNECTED||!mqttClient.connected()){
  server.handleClient();
    }
    
  mqttClient.loop();
}

void startAccessPoint(char* AP_NAME) {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_NAME);
  Serial.print("Access Point IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/save", handleSave);

  server.begin();
}

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Configure WiFi</h1>";
  html += "<form method='POST' action='/save'>";
  html += "SSID: <input type='text' name='ssid'><br>";
  html += "Password: <input type='password' name='password'><br>";
  html += "<input type='submit' value='Save'>";
  html += "</form>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleSave() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");

  // Save credentials to EEPROM
  for (int i = 0; i < ssid.length(); ++i) {
    EEPROM.write(i, ssid[i]);
  }
  EEPROM.write(ssid.length(), '\0');  // Null-terminate the SSID string

  for (int i = 0; i < password.length(); ++i) {
    EEPROM.write(i + 32, password[i]);
  }
  EEPROM.write(password.length() + 32, '\0');  // Null-terminate the password string
  EEPROM.commit();

  server.send(200, "text/html", "<h1>Configuration Saved</h1>");

  // Restart ESP8266 to connect with the new credentials
  ESP.restart();
}

void connectToWiFi() {
    unsigned long WIFI_Connection_TIMER = millis();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("\n Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    // wait till wifi connects 
    if(millis()-WIFI_Connection_TIMER>7000){ // delay 7 seconds trying to connect to wifi
      // failed to connect to wifi
          Serial.println("\n Failed to connect to wifi --> configuring a hot spot");
          startAccessPoint("Unimote Credentials !");
          break;
      }
  }
if(WiFi.status() == WL_CONNECTED){
  Serial.println();
  Serial.print("Connected to WiFi. IP address: ");
  Serial.println(WiFi.localIP());}
}
