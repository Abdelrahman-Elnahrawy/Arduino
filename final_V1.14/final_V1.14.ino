#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_NeoPixel.h>


Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, 2, NEO_GRB + NEO_KHZ400);

ESP8266WebServer server(80);
IPAddress local_IP(192,168,4,22);
IPAddress gateway  (192,168,4,9);
IPAddress subnet (255,255,255,0);
String eeprom;
String  USR  ;
String PASS  ;
int     f    ;
int mq=1;
const char* mqtt_server = "192.168.1.123";
const char* mqtt_username = "zabolaa";
const char* mqtt_password = "zabolaa";
const char* Pub = "pub";
const char* Sub = "sub";
WiFiClient espClient;
PubSubClient client(espClient);
int MSG_NO=0;
int  T=0    ;
int LM=0    ;
int  S=0    ;
int T1=0    ;
int LD=10000; 
unsigned long lastMsg    = 0; 
unsigned long button_time= 0;
unsigned long temp_time=   0;
unsigned long mqtt_time=   0;
bool R1     = 0;
bool R2     = 0;
bool R3     = 0;
bool R4     = 0;
int  R5     = 0;
int  MS     = 3; // motion sensor
int  relay1 = 4; 
int  relay2 = 5;  
int  relay3 = 0;  
int  relay4 =15; 
int  relay5 =16; 
int  KP_1   =14;
int  KP_2   =12;
int  KP_3   =13;
int  pn     =0 ; //password begin byte in the eebrom
bool   chk = 0 ; //wifi connection info / if 1 hot spot mode if 0 then wifi mode.

#define MSG_BUFFER_SIZE  (80)
char msg[MSG_BUFFER_SIZE];

const String postForms = "<html>\
  <head>\
    <title>ESP8266 Web Server POST handling</title>\
    <style>\
 body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
     </form>\
    <h1>put the user name and password</h1><br>\
     <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/postform/\">\
        <input type=\"text\" name=\"SSID\" value=\"SSID\"><br>\
        <input type=\"text\" name=\"PASSWORD\" value=\"PASSWORD\"><br>\
        <input type=\"submit\" value=\"Submit\">\
    </form>\
  </body>\
</html>";

void handleRoot() {yield();
  server.send(200, "text/html", postForms);
}
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }}
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
void setup_wifi(){
  yield(); 
  Serial.println();
  Serial.println("trying to connect to wifi");
  USR ="";
  PASS="";
  for(int n=0; (char)EEPROM.read(n)!='^';n++){
    USR+=(char)EEPROM.read(n);
  f=n;
  yield(); 
  if (n>50){break;}  }
  for(int n=f+2; (char)EEPROM.read(n)!='^';n++){
    PASS+=(char)EEPROM.read(n);
    yield(); 
      if (n>100){break;} }
    WiFi.begin(USR,PASS);
    WiFi.mode(WIFI_STA);
    chk=true;
    Serial.println("");
    for(unsigned long temp_time=millis(); WiFi.status() != WL_CONNECTED;yield()) {
      if(chk==true){
        delay(1);
      Serial.print("Username:");  
        Serial.print(USR);
        Serial.println("");
      Serial.print("Password:");
      Serial.println(PASS);} 
    chk=false;
    if (millis()-temp_time>7000){
    Serial.println("Failed to connect to wifi ; configuring a hot spot");
    Serial.print("IP address: ");
    WiFi.softAPConfig(local_IP, gateway, subnet) ;
    Serial.println(WiFi.softAPIP());
    WiFi.softAP("ESP help!!");
    chk=true;
    break;}
    }
    if (chk==false){
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(USR);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());}
  }
void handleForm() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
String USR= "";
String PASS="";
    USR +=server.arg(0);
    PASS +=server.arg(1);
    eeprom=USR+"^"+PASS+"^";
    for(int n=0; n< eeprom.length();n++){
    yield(); 
  EEPROM.write(n,eeprom[n]);}
  EEPROM.commit();
    Serial.print("the user name is : ");
    Serial.println(USR);
     Serial.print("the user password is : ");
    Serial.println(PASS);
    server.send(200,"text/plain", "On the way");
    WiFi.softAPdisconnect (true);
    Serial.println("retry to connect");
   ESP.restart();}
    yield(); }
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) { yield();
    Serial.print((char)payload[i]);
      yield(); }
  Serial.println();
if ((char)payload[0] == '~'){
  for (int n=1;payload[n]!='~';n++){
  EEPROM.write(n-1,(char)payload[n]);
 
  yield();
}
  EEPROM.commit();
  Serial.println("a new wifi data is entered"); 
  ESP.restart();
}
if ((char)payload[5] == 'R'&&(char)payload[6] == '2'){
if((char)payload[8] == '1'){R2=1;}
else  { R2=0;}
digitalWrite(relay2,R2);
EEPROM.write(102,R2);
}


if ((char)payload[10] == 'R'&&(char)payload[11] == '3'){
if((char)payload[13] == '1'){R3=1;}
  else  {R3=0;}
digitalWrite(relay3,R3);
EEPROM.write(103,R3);
}   
if ((char)payload[15] == 'R'&&(char)payload[16] == '4'){
if((char)payload[18] == '1'){R4=1;}
  else  {R4=0;}
digitalWrite(relay4,R4);
EEPROM.write(104,R4);
} 

  if ((char)payload[20] == 'R'&&(char)payload[21] == '5'){
 R5 = ((int)payload[23]-48)*100+((int)payload[24]-48)*10+((int)payload[25]-48);
 if (R5>240){R5=256;
digitalWrite(relay5,HIGH);}
else{
analogWrite (relay5,R5);}
EEPROM.write(105,R5);}
if ((char)payload[30] == 'S'){ LM=1;
 EEPROM.write(110,LM);}
if ((char)payload[30] == 'A'){ LM=2;
 EEPROM.write(110,LM);}
 if ((char)payload[30] == 'M'){ LM=3;
 EEPROM.write(110,LM);}
   if ((char)payload[0] == 'R'&&(char)payload[1] == '1'){
    if((char)payload[3] == '1'){R1=1;}
    if((char)payload[3] == '0'){R1=0; 
    LM=LM-1;
    if(LM<0){LM=3;}} 
  if ((char)payload[33] == 'D'){
 LD = ((int)payload[35]-48)*1000+((int)payload[36]-48)*100+((int)payload[37]-48)*10+((int)payload[38]-48);
 EEPROM.write(106,(int)(payload[35]-48));
 EEPROM.write(107,(int)(payload[36]-48));
 EEPROM.write(108,(int)(payload[37]-48));
 EEPROM.write(109,(int)(payload[38]-48));
 } 

      
     digitalWrite(relay1,R1);
      EEPROM.write(101,R1);}
      S = (((int)payload[40]-48)*1000+((int)payload[41]-48)*100+((int)payload[42]-48)*10+((int)payload[43]-48));
   
 EEPROM.commit();  
   snprintf (msg, MSG_BUFFER_SIZE, "MSG No. #%d recived",S);
   
   client.publish(Pub, msg);  
    yield();  }

void reconnect() {
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "zabolaa";

     if (client.connect((char*) clientId.c_str(), mqtt_username, mqtt_password)) {
        yield(); 
       client.publish(Pub, "slave is on");
      Serial.print("\tMTQQ Connected");
      client.subscribe(Sub);
     yield();    }
else {
      Serial.println("failed"); 
      yield(); 
    }
  }
}
void http_forum_load(){
if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
    yield(); }

 server.on("/", handleRoot);
 server.on("/postform/", handleForm);
  server.begin();
  Serial.println("HTTP server started");}
void setup() {
  pinMode(A0      ,  INPUT); //ADC
  pinMode(relay1  , OUTPUT); //4
  pinMode(relay2  , OUTPUT); //5
  pinMode(relay3  , OUTPUT); //0
  pinMode(relay4  , OUTPUT); //15
  pinMode(relay5  , OUTPUT); //16
  pinMode(MS      ,  INPUT); //3
  pinMode(KP_1    ,  INPUT); //14
  pinMode(KP_2    ,  INPUT); //12
  pinMode(KP_3    ,  INPUT); //13
  EEPROM.begin(512);
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(50);
  strip.show();
  R1=EEPROM.read(101);
  R2=EEPROM.read(102);
  R3=EEPROM.read(103);
  R4=EEPROM.read(104);
  R5=EEPROM.read(105);
  LD=(EEPROM.read(106)*1000)+(EEPROM.read(107)*100)+(EEPROM.read(108)*10)+(EEPROM.read(109));
  LM=EEPROM.read(110);
  digitalWrite(relay1,R1);
  digitalWrite(relay2,R2);
  digitalWrite(relay3,R3);
  digitalWrite(relay4,R4);
  analogWrite (relay5,R5);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  if(chk==true){
http_forum_load();
}
 reconnect();
}

void loop() {
colorWipe(strip.Color(255, 0, 0), 50);
yield(); 
server.handleClient();
if(!client.connected()&&chk==false){
 if (millis() - lastMsg < 30000) {
 reconnect();
 }
  else {
  if(mq==1){
    mq=2;
      Serial.println("Failed to connect to MQTT server ; configuring a hot spot");
    Serial.print("IP address: ");
    WiFi.softAPConfig(local_IP, gateway, subnet) ;
    Serial.println(WiFi.softAPIP());
    http_forum_load();
    WiFi.softAP("MQTT server not found!!");
   mqtt_time=millis(); 
  } 
}

  }
if(millis()- mqtt_time > 60000 && mq==2 && !client.connected()){
 ESP.restart();}
 
 
client.loop();

if(millis() - temp_time > 60000){
temp_time=millis();
T=analogRead(A0);
Serial.print("in DegreeC=");

Serial.print("\t");

Serial.print(T);
}
 if(millis() - button_time > 700 ||digitalRead(KP_1)||digitalRead(KP_2)||digitalRead(KP_3)){
  button_time = millis();
if(digitalRead(KP_1)==0  && digitalRead(KP_2)==0&& digitalRead(KP_3)==1){
     R1=!R1;
     digitalWrite(relay1,R1);
     EEPROM.write(101,R1);
     LM=0;
     EEPROM.write(111,LM);}
if(digitalRead(KP_1)==0  && digitalRead(KP_2)==1&& digitalRead(KP_3)==0){R2=!R2;   
     digitalWrite(relay2,R2);
     EEPROM.write(102,R2);}
if(digitalRead(KP_1)==0  && digitalRead(KP_2)==1&& digitalRead(KP_3)==1){R3=!R3;  
     digitalWrite(relay3,R3);
     EEPROM.write(103,R3);}

if(digitalRead(KP_1)==1  && digitalRead(KP_2)==0&& digitalRead(KP_3)==0){R4=!R4;  
     digitalWrite(relay4,R4);
     EEPROM.write(104,R4);}
if(digitalRead(KP_1)==1  && digitalRead(KP_2)==0&& digitalRead(KP_3)==1){
  R5=R5+4; 
 button_time = button_time-690;   
  if (R5>256){R5=0;}
  if (R5<0  ){R5=256;}
  analogWrite(relay5,R5);
  EEPROM.write(105,R5)  ;
  if(R5==0){ button_time = button_time+1000;}
   }
  if(digitalRead(KP_1)==1  && digitalRead(KP_2)==1&& digitalRead(KP_3)==0){LM=LM-1;
  if (LM<1){LM=3;
  }
   EEPROM.write(111,LM);}
   if(digitalRead(KP_1)==1  && digitalRead(KP_2)==0&& digitalRead(KP_3)==0){/*Rx=!Rx;   
     digitalWrite(relayX,Rx);
     EEPROM.write(104,Rx);*/}
   
   EEPROM.commit();}         
 if (LM == 0){
 if(digitalRead(MS)==HIGH){R1=HIGH;}
  digitalWrite(relay1,R1);}
         
 if (LM == 1){
 if (digitalRead(MS)==HIGH) {
    T1= millis();
    R1=HIGH;
     }
    if (millis() - T1> LD) {R1=0;}
    digitalWrite(relay1,R1); }
    if (chk==false && client.connected()){
   if (millis() - lastMsg > 2000) {
    lastMsg = millis();
    ++MSG_NO;
    snprintf (msg, MSG_BUFFER_SIZE, "R1:%d R2:%d R3:%d R4:%d R5:%d T:%d D:%d LM:%d  #%ld ",R1,R2,R3,R4,R5,T,LD,LM,MSG_NO);

    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(Pub, msg);
  }}
}
