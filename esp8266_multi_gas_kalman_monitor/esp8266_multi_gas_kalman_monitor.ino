/*
 * Project: Multi-Gas & Temperature Monitor with Kalman Filtering
 * Author: Abdelrahman Elnahrawy
 * Sensors: MQ-2 (Smoke/LPG), MQ-5 (Natural Gas), MQ-9 (CO), LM35 (Temp)
 * Features: MQTT Data Logging, Kalman Filtering, Web Configuration
 */

#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <SimpleKalmanFilter.h>

// --- Pin Definitions ---
const int mq2Pin = 34;   // Analog Input (Note: ESP8266 has only 1 ADC (A0), 
const int mq5Pin = 35;   // if using ESP32, these pins are correct. 
const int mq9Pin = 36;   // For ESP8266, use an external ADC like ADS1115.)
const int lm35Pin = 39;  

// --- Kalman Filter Settings ---
// SimpleKalmanFilter(e_mea, e_est, q)
// e_mea: Measurement Uncertainty, e_est: Estimation Uncertainty, q: Process Noise
SimpleKalmanFilter mq2Kalman(2, 2, 0.01);
SimpleKalmanFilter mq5Kalman(2, 2, 0.01);
SimpleKalmanFilter mq9Kalman(2, 2, 0.01);
SimpleKalmanFilter lm35Kalman(2, 2, 0.01);

// ... (WiFi and MQTT Logic same as previous modules) ...

void loop() {
  // 1. Read Raw Values
  float rawMQ2 = analogRead(mq2Pin);
  float rawMQ5 = analogRead(mq5Pin);
  float rawMQ9 = analogRead(mq9Pin);
  float rawLM35 = analogRead(lm35Pin);

  // 2. Apply Kalman Filtering to remove noise
  float fMQ2 = mq2Kalman.updateEstimate(rawMQ2);
  float fMQ5 = mq5Kalman.updateEstimate(rawMQ5);
  float fMQ9 = mq9Kalman.updateEstimate(rawMQ9);
  float fTemp = lm35Kalman.updateEstimate(rawLM35);

  // 3. Conversion to Voltage (assuming 12-bit ADC 4095)
  float vMQ2 = fMQ2 * (3.3 / 4095.0);
  float vMQ5 = fMQ5 * (3.3 / 4095.0);
  float vMQ9 = fMQ9 * (3.3 / 4095.0);

  // 4. Gas Concentration Approximations (PPM)
  float lpgPPM = 2.5 * vMQ2; 
  float coPPM = 1.44 * (3.3 - vMQ9);
  float tempC = (fTemp * 3.3 * 100) / 4095.0;

  // 5. Publish to MQTT
  if (mqttClient.connected()) {
      char buffer[128];
      snprintf(buffer, 128, "{\"temp\":%.2f, \"lpg\":%.2f, \"co\":%.2f}", tempC, lpgPPM, coPPM);
      mqttClient.publish("environment/data", buffer);
  }

  // 6. Serial Output for Debugging
  Serial.print("Temp: "); Serial.print(tempC); Serial.println(" C");
  Serial.print("LPG: "); Serial.print(lpgPPM); Serial.println(" ppm");

  delay(5000); // 5-second interval
}#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#include <SimpleKalmanFilter.h>
#define HOTSPOT_MODE    0
#define NORMAL_OPERATION_MODE   1
char msg[50];
  char storedSSID[32];
  char storedPassword[32];
  char storedBroker[32];
unsigned long lastMsg = 0;
bool CurrentMode ;
int value = 0;

//mq pins

#define MQ_2_PIN  34 //GPIO05
#define MQ_5_PIN  35 //GPIO18
#define MQ_9_PIN  36 //GPIO23
#define TEMP_PIN  39//GPIO22

//wifi
const char* ssid = "";      // Initialize SSID
const char* password = "";  // Initialize password
const int eepromSize = 200;  // Size of EEPROM to store username and password

//mqtt
const char* mqttServer = "";
const int mqttPort = 1883;

const char* sub_Topic = "nosa";
const char* pub_Topic = "IR_RAW_DATA_TOPIC";
unsigned long LostConnectionTimer;
ESP8266WebServer server(80);
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);



void handleMQTTMessage(char* topic, byte* payload, unsigned int length) {

    
    Serial.println("IR raw data transmitted");
}

void connectToMQTT() {
  if(WiFi.status() != WL_CONNECTED){
    connectToWiFi();
    }
     mqttClient. setSocketTimeout (50);
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(handleMQTTMessage);

  unsigned long MQTT_Connection_TIMER = millis();
  
  while (!mqttClient.connected()) {

    Serial.print("Connecting to MQTT...");
    Serial.println(mqttServer);
  
    if (mqttClient.connect("ESP8266Clientomo")) {
      Serial.println("MQTT connected");
       mqttClient.publish(pub_Topic, "hello world");
      mqttClient.subscribe(sub_Topic);
    }
    else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 1 seconds...");
      delay(1000);
    }
       if(millis()-MQTT_Connection_TIMER>30000){
             Serial.println("failed to connect to mqtt --> starting hotspot");
      startAccessPoint("Unimote MQTT !");
      break;
      }
  }      
  }


void startAccessPoint(char* AP_NAME) {
  CurrentMode = HOTSPOT_MODE;
  LostConnectionTimer = millis(); // counting the time till retrying to connect
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_NAME);
  Serial.print("Access Point IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/save", handleSave);

  server.begin();
}

void handleRoot() {
  String html =
              "<html>"
              "<head>"
              "<meta charset=\"UTF-8\">"
              "<title>Configuration</title>"
              "<style>"
              "body {"
              "display: flex;"
              "justify-content: center;"
              "align-items: center;"
              "height: 100vh;"
              "background-color: #f2f2f2;"
              "font-family: Arial, sans-serif;"
              "}"
              ".container {"
              "width: 70%;"
              "padding: 20px;"
              "background-color: #ffffff;"
              "border-radius: 8px;"
              "box-shadow: 0 2px 4px rgba(0, 0, 0, 0.2);"
              "}"
              "h1 {"
              "text-align: center;"
              "margin: 1% 0;"
              "color: #333333;"
              "}"
              "label {"
              "display: block;"
              "margin-top: 5%;"
              "margin-bottom: 1%;"
              "color: #333333;"
              "}"
              "input[type=\"text\"],"
              "input[type=\"password\"] {"
              "width: 90%;"
              "padding: 2%;"
              "font-size: 100%;"
              "border: 5px solid #cccccc;"
              "border-radius: 40px;"
              "}"
              ".button-container {"
              "text-align: center;"
              "margin-top: 10px;"
              "}"
              ".button-container button {"
              "padding: 10px 16px;"
              "font-size: 16px;"
              "background-color: #4CAF50;"
              "border: none;"
              "color: white;"
              "cursor: pointer;"
              "border-radius: 10px;"
              "}"
              ".button-container button:hover {"
              "background-color: #45a049;"
              "border-radius: 40px;"
              "}"
              ".feedback-container {"
              "margin-top: 20px;"
              "padding: 10px;"
              "width: 90%;"
              "font-size: 100%;"
              "border: 5px solid #cccccc;"
              "border-radius: 8px;"
              "resize: none;"
              "background-color: #f9f9f9;"
              "text-align: left;"
              "}"
              "</style>"
              "</head>"
              "<body>"
              "<div class=\"container\">"
              "<h1>Welcome Home !</h1>"
              "<h4>Please enter the WiFi parameters and the server IP address</h4>"
              "<p>Notes default server IP usually 192.168.1.50</p>"
              "<form method='POST' action='/save'>"
              "<label for=\"wifi-ssid\">Wi-Fi SSID:</label>"
              "<input type=\"text\" id=\"wifi-ssid\" name=\"wifi-ssid\">"
              "<label for=\"wifi-password\">Wi-Fi Password:</label>"
              "<input type=\"password\" id=\"wifi-password\" name=\"wifi-password\">"
              "<label for=\"mqtt-broker\">Server IP:</label>"
              "<input type=\"text\" id=\"mqtt-broker\" name=\"mqtt-broker\">"
              "<div class=\"button-container\">"
              "<button type=\"submit\">Submit </button>"
              "</div>"
              "<div class=\"feedback-container\">"
              " <p id=\"feedback\"></p>"
              " </div>"
              "</form>"
              "</div>"
              
             " <script>"
             "  function submitForm(event) {"
             "   event.preventDefault();"
             "  const ssid = document.getElementById('wifi-ssid').value;"
             " const password = document.getElementById('wifi-password').value;"
             "const broker = document.getElementById('mqtt-broker').value;"

      // Display feedback
             "const feedbackElement = document.getElementById('feedback');"
             "feedbackElement.textContent = `SSID: ${ssid}, Password: ${password}, Broker: ${broker}`;"

      // You can perform further actions with the form values here
      // For example, make an HTTP request or update device settings
               "}"
              "</script>"
              
              "</body>"
              "</html>";

  server.send(200, "text/html", html);
}

void handleSave() {
   Serial.println("\n saving new parameters");
    Serial.print("SSID:");
    Serial.println(server.arg("wifi-ssid"));  
    Serial.print("pasword:");
    Serial.println(server.arg("wifi-password"));
        Serial.print("mqtt:");
    Serial.println(server.arg("mqtt-broker"));
      Serial.print("\n");
  String ssid = server.arg("wifi-ssid");
  String password = server.arg("wifi-password");
  String mqttServer = server.arg("mqtt-broker");
  

  // Save credentials to EEPROM
  for (int i = 0; i < ssid.length(); ++i) {
    EEPROM.write(i, ssid[i]);
  }
  EEPROM.write(ssid.length(), '\0');  // Null-terminate the SSID string

  for (int i = 0; i < password.length(); ++i) {
    EEPROM.write(i + 32, password[i]);
  }
  EEPROM.write(password.length() + 32, '\0');  // Null-terminate the password string
  
   for (int i = 0; i < mqttServer.length(); ++i) {
    EEPROM.write(i + 64, mqttServer[i]);
  }
  EEPROM.write(mqttServer.length() + 64, '\0');  // Null-terminate the password string
   
  
  EEPROM.commit();

  server.send(200, "text/html", "<h1>Configuration Saved</h1>");
  
delay(1000);
Serial.println("\n data reset restart");
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
void setup() {
   Serial.begin(115200);

    EEPROM.begin(eepromSize);
  CurrentMode =  NORMAL_OPERATION_MODE ;  // assuming the esp will work normally
  // Read stored username and password from EEPROM

  for (int i = 0; i < 32; ++i) {
    storedSSID[i] = EEPROM.read(i);
    storedPassword[i] = EEPROM.read(i + 32);
    storedBroker[i] = EEPROM.read(i + 64);
  }

  // Check if stored credentials are available
  if (strlen(storedSSID) > 0 && strlen(storedPassword) > 0 && strlen(storedBroker) > 0) {
    ssid = storedSSID;
    password = storedPassword;
    mqttServer = storedBroker;
    connectToWiFi();
  } else {
    startAccessPoint("Unimote Credentials !");
  }
      mqttClient.setKeepAlive(300); 
      mqttClient.setServer(mqttServer, 1883);
  
  if(WiFi.status() == WL_CONNECTED){
  connectToMQTT();
      mqttClient.publish(pub_Topic,"Node is ON");}
}

// Pin Definitions
const int mq2Pin = 34;   // Pin for MQ2 sensor
const int mq5Pin = 35;   // Pin for MQ5 sensor
const int mq9Pin = 36;   // Pin for MQ9 sensor
const int lm35Pin = 39;  // Pin for LM35 temperature sensor

// Kalman filter objects
SimpleKalmanFilter mq2KalmanFilter(2, 2, 0.01);
SimpleKalmanFilter mq5KalmanFilter(2, 2, 0.01);
SimpleKalmanFilter mq9KalmanFilter(2, 2, 0.01);
SimpleKalmanFilter lm35KalmanFilter(2, 2, 0.01);

void loop() {
  float mq2Value = analogRead(mq2Pin);
  float mq5Value = analogRead(mq5Pin);
  float mq9Value = analogRead(mq9Pin);
  float lm35Value = analogRead(lm35Pin);

  // Apply Kalman filter to sensor readings
  float mq2FilteredValue = mq2KalmanFilter.updateEstimate(mq2Value);
  float mq5FilteredValue = mq5KalmanFilter.updateEstimate(mq5Value);
  float mq9FilteredValue = mq9KalmanFilter.updateEstimate(mq9Value);
  float lm35FilteredValue = lm35KalmanFilter.updateEstimate(lm35Value);

  // Convert filtered sensor readings to voltage
  float mq2Voltage = mq2FilteredValue * (3.3 / 4095.0);
  float mq5Voltage = mq5FilteredValue * (3.3 / 4095.0);
  float mq9Voltage = mq9FilteredValue * (3.3 / 4095.0);

  // Gas equations for MQ-2 sensor (approximations)
  float mq2LPG = 2.5 * mq2Voltage;
  float mq2Propane = 2.5 * mq2Voltage;
  float mq2Methane = 2.5 * mq2Voltage;
  float mq2Alcohol = 2.5 * mq2Voltage;
  float mq2Hydrogen = 2.5 * mq2Voltage;
  float mq2Smoke = 2.5 * mq2Voltage;

  // Gas equation for MQ-5 sensor (approximation)
  float mq5LPG = 3.027 * mq5Voltage;

  // Gas equation for MQ-9 sensor (approximation)
  float mq9CO = 1.44 * (3.3 - mq9Voltage);

  // Temperature equation for LM35 sensor
  float lm35Temp = (lm35FilteredValue * 3.3 * 100) / 4095.0;

  Serial.println("Sensor Data:");
  Serial.print("MQ2 - LPG: ");
  Serial.print(mq2LPG);
  Serial.print(" ppm, Propane: ");
  Serial.print(mq2Propane);
  Serial.print(" ppm, Methane: ");
  Serial.print(mq2Methane);
  Serial.print(" ppm, Alcohol: ");
  Serial.print(mq2Alcohol);
  Serial.print(" ppm, Hydrogen: ");
  Serial.print(mq2Hydrogen);
  Serial.print(" ppm, Smoke: ");
  Serial.print(mq2Smoke);
  Serial.println(" ppm");

  Serial.print("MQ5 - LPG: ");
  Serial.print(mq5LPG);
  Serial.println(" ppm");

  Serial.print("MQ9 - CO: ");
  Serial.print(mq9CO);
  Serial.println(" ppm");

  Serial.print("LM35 - Temperature: ");
  Serial.print(lm35Temp);
  Serial.println(" °C");

  delay(5000);
}
