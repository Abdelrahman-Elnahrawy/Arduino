#include <Adafruit_NeoPixel.h>
#define BRIGHTNESS 50
#define neopixel  14
Adafruit_NeoPixel strip(30, neopixel, NEO_GRB + NEO_KHZ800);


#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
#define HOTSPOT_MODE    0
#define NORMAL_OPERATION_MODE   1
char msg[50];
  char storedSSID[32];
  char storedPassword[32];
  char storedBroker[32];
unsigned long lastMsg = 0;
bool CurrentMode ;
int value = 0;
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
  if (strcmp(topic, sub_Topic) == 0) {
    Serial.println("Received IR raw data");
    
    // Transmit the IR raw data
    for (unsigned int i = 0; i < length; i++) {
      //irSender.sendRaw(payload[i], 32, kHz);
      delay(50); // Adjust delay as needed
    }
    
    Serial.println("IR raw data transmitted");
  }
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
      //mqttClient.subscribe(sub_Topic);
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


        pinMode (neopixel , OUTPUT);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
}

void loop() {
      if(WiFi.status() != WL_CONNECTED && CurrentMode ==  NORMAL_OPERATION_MODE){
                 Serial.println("wifi connection lost");
        connectToWiFi();}
    if(CurrentMode == HOTSPOT_MODE ){
      if(millis()-LostConnectionTimer>180000){
         Serial.println(" \n 3 mintues without reseting , trying to reconnect");
        ESP.restart();}
      else{server.handleClient(); }
     }
  if (!mqttClient.connected() && CurrentMode ==  NORMAL_OPERATION_MODE) {
    Serial.println("LoSt connection !!");
    if(WiFi.status() != WL_CONNECTED){connectToWiFi();}
    else{
          Serial.print("mqtt state");
          Serial.println(mqttClient.state());
      connectToMQTT();}
  }
  if(CurrentMode ==  NORMAL_OPERATION_MODE && mqttClient.connected()){
    
  // mqttClient.loop(); 
  unsigned long now = millis(); 
  if (now - lastMsg > 1000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 50, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    mqttClient.publish(pub_Topic, msg);
  }
  
  }

}





void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
  
void specific_clear(int pixels[]) {
  for(int i=0; i<strip.numPixels(); i++) { 
  for (int x=0; x<sizeof(pixels); x=x+1){
  if (pixels[x] == i){
      strip.setPixelColor(i, strip.Color(247, 0, 255));
      strip.show();    
      delay(10);
    }
    }      //  Set pixel's color (in RAM)                       //  Update strip to match                           //  Pause for a moment
  }
}
void specific(int pixels[]) {
  
  for(int i=0; i<strip.numPixels(); i++) { 
  for (int x=0; x<sizeof(pixels); x=x+1){
  if (pixels[x] == i){
      strip.setPixelColor(i, strip.Color(255,215,0));
      strip.show();   
      delay(10); 
    }
    }      //  Set pixel's color (in RAM)                       //  Update strip to match                           //  Pause for a moment
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
