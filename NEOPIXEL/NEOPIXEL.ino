

#include <Adafruit_NeoPixel.h>
#define BRIGHTNESS 50
#define neopixel  14
Adafruit_NeoPixel strip(30, neopixel, NEO_GRB + NEO_KHZ800);
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <PubSubClient.h>
volatile uint32_t lastMillis = 0;

#define BUILTIN_LED     2 

#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     1

// Select a Timer Clock
#define USING_TIM_DIV1                false           // for shortest and most accurate timer
#define USING_TIM_DIV16               false           // for medium time and medium accurate timer
#define USING_TIM_DIV256              true            // for longest timer but least accurate. Default

#include "ESP8266TimerInterrupt.h"

ESP8266Timer ITimer;

const unsigned long interval = 1000; // 1 second interval

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
  int statusLed =1;
void IRAM_ATTR Server_Update_Loop()
{Serial.println("Wi am in here");
 /*   if(WiFi.status() != WL_CONNECTED||!mqttClient.connected()){
  server.handleClient();
    }
  mqttClient.loop();*/

   digitalWrite(BUILTIN_LED, statusLed);  //Toggle LED Pin
  statusLed = !statusLed;
  break;
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
  
  pinMode (neopixel , OUTPUT);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
  Serial.println("Ready.");
  /*
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  theaterChase(strip.Color(127, 127, 127), 50); // White
  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
  */
     if (ITimer.attachInterruptInterval(500, Server_Update_Loop))
  {
    lastMillis = millis();
    Serial.print(F("Starting ITimer OK, millis() = ")); Serial.println(lastMillis);
  }
  else
    Serial.println(F("Can't set ITimer correctly. Select another freq. or interval"));

}


void loop() {

}

// Fill the dots one after the other with a color
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

//Theatre-style crawling lights with rainbow effect
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
