
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
ESP8266WebServer server(80);
IPAddress local_IP(192,168,4,22);
IPAddress gateway  (192,168,4,9);
IPAddress subnet (255,255,255,0);
String eeprom;
String  USR  ;
String PASS  ;
int     f    ;
String ID ="1";
int mq=1;
unsigned long temo = 0;
const char* mqtt_server = "192.168.1.123";
const char* mqtt_username = "username";
const char* mqtt_password = "password";
const char* Pub = "PC-response";
const char* Sub = "PC-force";
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
unsigned long lastMsg2 = 0;
unsigned long TTR     = 0; //time till release
unsigned long TP      = 0; 
unsigned long temp_time=   0;
unsigned long mqtt_time=   0;
int MSG_NO = 0;
bool chk   = 0; 
int  Power = 5;
int  PWR_IN=13;
int  Reset = 4;
int  Time  =-1;
bool Bp    = 0;
#define MSG_BUFFER_SIZE  (50)
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
  WiFi.softAP("WiFi!PCCID: "+ID);
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
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();


if ((char)payload[0] == 'c'&&(char)payload[1] == 'a'){
TP = millis();
Time=-1;
client.publish(Pub, "Shutdown cancelled !!");
}
if ((char)payload[0] == 'R'&&(char)payload[1] == 'e'){
TP = millis();
TTR= 2000;
    client.publish(Pub, "restart on the way");
digitalWrite(Reset,LOW);

Bp=1;
Time=-1;
}
//shutdown in :2000
if ((char)payload[0] == 'S'&&(char)payload[1] == 'h'){
      client.publish(Pub, "Power button is pressed");
TP = millis();
TTR= 2000;
digitalWrite(Power,LOW);
Bp=1;
Time=-1;
 }
 if ((char)payload[0] == 'F'&&(char)payload[1] == 'o'){
   client.publish(Pub, "Force Shutdown on the way");
TP = millis();
TTR= 11000;

digitalWrite(Power,LOW);
Time=-1;
Bp=1;
 }
 if ((char)payload[0] == 'i'&&(char)payload[1] == 'n'){
 Time = ((int)payload[3]-48)*10000+((int)payload[4]-48)*1000+((int)payload[5]-48)*100+((int)payload[6]-48)*10+((int)payload[7]-48); 
 } 
}
void reconnect() {
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
       String clientId = "PCCID:"+ID;

     if (client.connect((char*) clientId.c_str(), mqtt_username, mqtt_password)) {
        yield(); 
       client.publish(Pub, "slave is on");
      Serial.print("\tMTQQ Connected");
      client.subscribe(Sub);
     yield();    }
else {
      Serial.println("failed to connect to mqtt"); 
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
   pinMode(PWR_IN , INPUT);
  pinMode(Power  , OUTPUT);
  digitalWrite(Power,HIGH);
  pinMode(Reset  , OUTPUT);
  digitalWrite(Reset,HIGH);
  EEPROM.begin(512);
  Serial.begin(115200);


  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  if(chk==true){http_forum_load();}
    else{reconnect();}
}


void loop() {
yield(); 
server.handleClient();
if(!client.connected()&&chk==false){
 if (millis() - lastMsg < 20000) {
 reconnect();
 }
  else {
  if(mq==1){
   Serial.println("Failed to connect to MQTT server ; configuring a hot spot");
    Serial.print("IP address: ");
    WiFi.softAPConfig(local_IP, gateway, subnet) ;
    Serial.println(WiFi.softAPIP());
     WiFi.softAP("MQTT!PCCID: "+ID);
    mq=2;
   mqtt_time=millis();
    http_forum_load();} 
}
 }



client.loop();
yield() ;
if (chk==false && client.connected()){
    if (Time >= 0){  
 if (millis() - lastMsg > 1000) {
    lastMsg = millis();
    ++MSG_NO;
     Time = Time - 1;
     if (Time >0){
    snprintf (msg, MSG_BUFFER_SIZE, "Shutdown in %d seconds#%d",Time,MSG_NO);}
       if (Time <=0){
    snprintf (msg, MSG_BUFFER_SIZE, "Shutdown NOW#%d",MSG_NO);}
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(Pub, msg);
    if (Time == 0){
    digitalWrite(Power,LOW);
    Bp=1;
    TP= millis();
    TTR=2000;}
  }
  }
  
    if (millis() - lastMsg2 > 2000){
    lastMsg2 = millis();
    if(digitalRead(PWR_IN)==HIGH){
      snprintf (msg, MSG_BUFFER_SIZE, "ON");
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(Pub, msg);}
    else{      
      snprintf (msg, MSG_BUFFER_SIZE, "OFF");
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(Pub, msg);
      }
    }
}
  if( Bp==1 && millis() - TP > TTR ){
    Time =-1;
    digitalWrite(Power,HIGH);
    digitalWrite(Reset,HIGH);
    Bp=0;
  }
     if (WiFi.status() != WL_CONNECTED&&temo==0){  Serial.println("Wifi disconnected .... begin the count down till restart");
    temo=millis();}
     if (!client.connected()&&temo==0){  Serial.println("MqTT disconnected .... begin the count down till restart");
    temo=millis(); }
    if (client.connected()&&temo>0){ Serial.println("MqTT Connected .... begin the count down till restart");
      temo=0; }
    
 if (millis()-temo>300000){
  
  Serial.println();
  Serial.println("i am restarting");
  ESP.restart();}

}
