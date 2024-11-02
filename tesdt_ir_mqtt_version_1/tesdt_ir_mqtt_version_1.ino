#include <ESP8266WiFi.h>

#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
ESP8266WebServer server(80);
IPAddress subnet (255,255,255,0);
IPAddress local_IP(192,168,4,22);
IPAddress gateway  (192,168,4,9);

String ID = "10";
String eeprom;
String  USR  ;
String PASS  ;
int     f    ;
int      mq=1;
int  pn     =0 ; 
bool   chk = 0 ;
unsigned long mqtt_time= 0;
unsigned long temo = 0;

const char* mqtt_server = "broker.emqx.io";

const char* Pub = "IR_Pub";
const char* Sub = "IR_Sub";

uint16_t rawData[99];


int D=0;
const uint16_t kIrLed = 13; 
IRsend irsend(kIrLed); 
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(999)
char msg[MSG_BUFFER_SIZE];
int value = 0;
int q=0;
int z=1;


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

void handleRoot() {
  server.send(200, "text/html", postForms);
}

void setup_wifi(){
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
      if (n>100){break;}}
   
    WiFi.begin(USR,PASS);
    WiFi.mode(WIFI_STA);
    chk=true;
    Serial.println("");
 
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

     if ((char)payload[0] == '('||(char)payload[0] == '*'||(char)payload[0] == '-'||(char)payload[0] == '_'||(char)payload[0] == '?') {
     if ((char)payload[0] == '('){
 for( int q = 0 ; q< 20; q=q+1){

      int z1 =  z+1 ;
      int z2 = z1+1 ;
      int z3 = z2+1 ;     
      int D = ((int)payload[z]-48)*1000+((int)payload[z1]-48)*100+((int)payload[z2]-48)*10+((int)payload[z3]-48); 
       rawData[q]=(int)D ;
      z=z+5;}
      z=1;}
      if ((char)payload[0] == '*'){
 for( int q = 20 ; q< 40; q=q+1){

      int z1 =  z+1 ;
      int z2 = z1+1 ;
      int z3 = z2+1 ; 
      int D = ((int)payload[z]-48)*1000+((int)payload[z1]-48)*100+((int)payload[z2]-48)*10+((int)payload[z3]-48); 
      rawData[q]=D ;
      z=z+5;}
      z=1;}
           if ((char)payload[0] == '-'){
 for( int q = 40 ; q< 60; q=q+1){

      int z1 =  z+1 ;
      int z2 = z1+1 ;
      int z3 = z2+1 ;
      int D = ((int)payload[z]-48)*1000+((int)payload[z1]-48)*100+((int)payload[z2]-48)*10+((int)payload[z3]-48); 
      rawData[q]=D ;
      z=z+5;}
      z=1;}
           if ((char)payload[0] == '_'){
 for( int q = 60 ; q< 80; q=q+1){

      int z1 =  z+1 ;
      int z2 = z1+1 ;
      int z3 = z2+1 ; 
      int D = ((int)payload[z]-48)*1000+((int)payload[z1]-48)*100+((int)payload[z2]-48)*10+((int)payload[z3]-48); 
      rawData[q]=D ;
      z=z+5;}
      z=1;}
           if ((char)payload[0] == '?'){
 for( int q = 80 ; q< 100; q=q+1){

      int z1 =  z+1 ;
      int z2 = z1+1 ;
      int z3 = z2+1 ; 
      int D = ((int)payload[z]-48)*1000+((int)payload[z1]-48)*100+((int)payload[z2]-48)*10+((int)payload[z3]-48); 
      rawData[q]=D ;
      z=z+5;}
      z=1;
      irsend.sendRaw(rawData, 99, 38);
       snprintf (msg, MSG_BUFFER_SIZE, "the messege sent #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("IROUT", msg);
    value = value +1;
        client.publish(Pub, "IR send!");
}
for(int i = 0; i < 99; i++){Serial.print((int)rawData[i]);Serial.print(",");}
Serial.println();z=1;}
}

void connectMqTT() {
  if (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "IR"+ID;

  if (client.connect((char*) clientId.c_str())) {
        yield(); 
       client.publish(Pub, "slave is on");
      Serial.print("\tMQTT Connected\n");
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
  int X=0;
  irsend.begin();     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  EEPROM.begin(512);
  
setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  if(chk==true){http_forum_load();}
    else{connectMqTT();}
}

void loop() {

yield(); 
server.handleClient();
if(!client.connected()&&chk==false){
 if (millis() - lastMsg < 20000) {
 connectMqTT();
 }
  else {
  if(mq==1){
   Serial.println("Failed to connect to MQTT server ; configuring a hot spot");
    Serial.print("IP address: ");
    WiFi.softAPConfig(local_IP, gateway, subnet) ;
    Serial.println(WiFi.softAPIP());

    WiFi.softAP("MQTT!IRID: "+ID);
    mq=2;
   mqtt_time=millis();
    http_forum_load();} 
}
 }

client.loop();

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
