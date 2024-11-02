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
String ID ="2";
const char* Pub = "ESP_Pub_2";
const char* Sub = "ESP_Sub_2";
String USR   ;
String PASS  ;
int    f     ;
int    mq=1  ;
const char* mqtt_server = "192.168.1.123";
const char* mqtt_username =   "username" ;
const char* mqtt_password =   "password" ;
WiFiClient espClient;
PubSubClient client(espClient);
int MSG_NO=0;
int  T=0    ;
int LM=0    ;
int  S=0    ;
int T1=0    ;
int LD=10000; 
unsigned long temo       = 0;
unsigned long lastMsg    = 0;
unsigned long button_time= 0;
unsigned long temp_time  = 0;
unsigned long mqtt_time  = 0;
unsigned long alrm       = 0;
unsigned long TtT        = 0;
bool sun    = 0;
bool R0     = 0;
bool R1     = 0;
bool R2     = 0;
bool R3     = 0;
bool R4     = 0;
bool R5     = 0;
bool R6    =  0;
bool R7     = 0;
bool R8     = 0;
bool R9     = 0;
bool R10    = 0;
bool R11    = 0;
int PWM0    = 0;
int PWM1    = 0;
int PWM2    = 0;
int PWM3    = 0;
int PWM4    = 0;
int PWM5    = 0;

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

void handleRoot() {
  
  yield();
  server.send(200, "text/html", postForms);
}
void setup_wifi(){
  yield(); 
  //Serial.println();
  //Serial.println("trying to connect to wifi");
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
    //Serial.println("");
    for(unsigned long temp_time=millis(); WiFi.status() != WL_CONNECTED;yield()) {

      
      if(chk==true){
        delay(1);
      //Serial.print("Username:");  
        //Serial.print(USR);
        //Serial.println("");
      //Serial.print("Password:");
      //Serial.println(PASS);
      } 
    chk=false;
    if (millis()-temp_time>7000){
    //Serial.println("Failed to connect to wifi ; configuring a hot spot");
    //Serial.print("IP address: ");
    WiFi.softAPConfig(local_IP, gateway, subnet) ;
    //Serial.println(WiFi.softAPIP());
    WiFi.softAP("WiFi!RCID: "+ID);
    chk=true;
    break;}
    }
    if (chk==false){
  //Serial.println("");
  //Serial.print("Connected to ");
  //Serial.println(USR);
  //Serial.print("IP address: ");
  //Serial.println(WiFi.localIP());
  }
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
    //Serial.print("the user name is : ");
    //Serial.println(USR);
     //Serial.print("the user password is : ");
    //Serial.println(PASS);
    server.send(200,"text/plain", "On the way");
    WiFi.softAPdisconnect (true);
    //Serial.println("retry to connect");
   ESP.restart();}
    yield(); }
void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("Message arrived [");
  //Serial.print(topic);
  //Serial.print("] ");
  for (int i = 0; i < length; i++) { yield();
    //Serial.print((char)payload[i]);
      yield(); }
  //Serial.println();

  
if ((char)payload[0] == '~'){
  for (int n=1;payload[n]!='~';n++){
  EEPROM.write(n-1,(char)payload[n]);
 if(n>98){break;}
  yield();
}
  EEPROM.commit();
  //Serial.println("a new wifi data is entered"); 
  ESP.restart();
}
if ((char)payload[0] == 'R'&&(char)payload[1] == '0'&&(char)payload[2] == ':'){
if((char)payload[3] == '1'){R0=1;}
else  { R0=0;}
EEPROM.write(100,R0);
Serial.print("R0:");Serial.println(R0);
}
if ((char)payload[0] == 'R'&&(char)payload[1] == '1'&&(char)payload[2] == ':'){
if((char)payload[3] == '1'){R1=1;}
else  { R1=0;}
EEPROM.write(101,R1);
Serial.print("R1:");Serial.println(R1);
}

if ((char)payload[0] == 'R'&&(char)payload[1] == '2'&&(char)payload[2] == ':'){
if((char)payload[3] == '1'){R2=1;}
else  { R2=0;}
EEPROM.write(102,R2);
Serial.print("R2:");Serial.println(R2);
}

if ((char)payload[0] == 'R'&&(char)payload[1] == '3'&&(char)payload[2] == ':'){
if((char)payload[3] == '1'){R3=1;}
else  { R3=0;}
EEPROM.write(103,R3);
Serial.print("R3:");Serial.println(R3);
}


if ((char)payload[0] == 'R'&&(char)payload[1] == '4'&&(char)payload[2] == ':'){
if((char)payload[3] == '1'){R4=1;}
else  { R4=0;}
EEPROM.write(104,R4);
Serial.print("R4:");Serial.println(R4);
}

if ((char)payload[0] == 'R'&&(char)payload[1] == '5'&&(char)payload[2] == ':'){
if((char)payload[3] == '1'){R5=1;}
else  { R5=0;}
EEPROM.write(105,R5);
Serial.print("R5:");Serial.println(R5);
}


if ((char)payload[0] == 'R'&&(char)payload[1] == '6'&&(char)payload[2] == ':'){
if((char)payload[3] == '1'){R6=1;}
else  { R6=0;}
EEPROM.write(106,R6);
Serial.print("R6:");Serial.println(R6);
}


if ((char)payload[0] == 'R'&&(char)payload[1] == '7'&&(char)payload[2] == ':'){
if((char)payload[3] == '1'){R7=1;}
else  { R7=0;}
EEPROM.write(107,R7);
Serial.print("R7:");Serial.println(R7);
}


if ((char)payload[0] == 'R'&&(char)payload[1] == '8'&&(char)payload[2] == ':'){
if((char)payload[3] == '1'){R8=1;}
else  { R8=0;}
EEPROM.write(108,R8);
Serial.print("R8:");Serial.println(R8);
}

if ((char)payload[0] == 'R'&&(char)payload[1] == '9'&&(char)payload[2] == ':'){
if((char)payload[3] == '1'){R9=1;}
else  { R9=0;}
EEPROM.write(109,R9);
Serial.print("R9:");Serial.println(R9);
}
if ((char)payload[0] == 'R'&&(char)payload[1] == '1'&&(char)payload[2] == '0'){
if((char)payload[3] == '1'){R10=1;}
else  { R10=0;}
EEPROM.write(110,R10);
Serial.print("R10:");Serial.println(R10);
}


if ((char)payload[0] == 'R'&&(char)payload[1] == '1'&&(char)payload[2] == '1'){
if((char)payload[3] == '1'){R11=1;}
else  { R11=0;}
EEPROM.write(111,R11);
Serial.print("R11:");Serial.println(R11);
}

  if ((char)payload[0] == 'P'&&(char)payload[1] == 'W'&&(char)payload[2] == 'M'&&(char)payload[3] == '0'&&(char)payload[4] == ':'){
PWM0 = ((int)payload[5]-48)*100+((int)payload[6]-48)*10+((int)payload[7]-48);
  if (PWM0<0){PWM0=0;}
 if (PWM0>240){PWM0=255;}
Serial.print("PWM0:");Serial.println(PWM0);
EEPROM.write(112,PWM0);}

  if ((char)payload[0] == 'P'&&(char)payload[1] == 'W'&&(char)payload[2] == 'M'&&(char)payload[3] == '1'&&(char)payload[4] == ':'){
PWM1 = ((int)payload[5]-48)*100+((int)payload[6]-48)*10+((int)payload[7]-48);
  if (PWM1<0){PWM1=0;}
 if (PWM1>240){PWM1=255;}
Serial.print("PWM1:");Serial.println(PWM1);
EEPROM.write(113,PWM1);}


  if ((char)payload[0] == 'P'&&(char)payload[1] == 'W'&&(char)payload[2] == 'M'&&(char)payload[3] == '2'&&(char)payload[4] == ':'){
PWM2 = ((int)payload[5]-48)*100+((int)payload[6]-48)*10+((int)payload[7]-48);
  if (PWM2<0  ){PWM2=0;}
 if  (PWM2>240){PWM2=255;}
Serial.print("PWM2:");Serial.println(PWM2);
EEPROM.write(114,PWM2);}

  if ((char)payload[0] == 'P'&&(char)payload[1] == 'W'&&(char)payload[2] == 'M'&&(char)payload[3] == '3'&&(char)payload[4] == ':'){
PWM3 = ((int)payload[5]-48)*100+((int)payload[6]-48)*10+((int)payload[7]-48);
  if (PWM3<0){PWM3=0;}
 if (PWM3>240){PWM3=255;}
Serial.print("PWM3:");Serial.println(PWM3);
EEPROM.write(115,PWM3);}

  if ((char)payload[0] == 'P'&&(char)payload[1] == 'W'&&(char)payload[2] == 'M'&&(char)payload[3] == '4'&&(char)payload[4] == ':'){
PWM4 = ((int)payload[5]-48)*100+((int)payload[6]-48)*10+((int)payload[7]-48);
  if (PWM4<0) {PWM4=0;}
 if (PWM4>240){PWM4=255;}
Serial.print("PWM4:");Serial.println(PWM4);
EEPROM.write(116,PWM0);}

  if ((char)payload[0] == 'P'&&(char)payload[1] == 'W'&&(char)payload[2] == 'M'&&(char)payload[3] == '5'&&(char)payload[4] == ':'){
PWM5 = ((int)payload[5]-48)*100+((int)payload[6]-48)*10+((int)payload[7]-48);
  if (PWM5<0 ){PWM5=  0;}
 if (PWM5>240){PWM5=255;}
Serial.print("PWM5:");Serial.println(PWM5);
EEPROM.write(117,PWM5);}

 if ((char)payload[35] == 'M'){ LM=0;
 EEPROM.write(111,LM);}
if ((char)payload[35] == 'S'){ LM=1;
 EEPROM.write(111,LM);}
if ((char)payload[35] == 'A'){ LM=2;
 EEPROM.write(111,LM);}
 
  if ((char)payload[38] == 'D'){
 LD = ((int)payload[40]-48)*1000+((int)payload[41]-48)*100+((int)payload[42]-48)*10+((int)payload[43]-48);
 EEPROM.write(107,(int)(payload[40]-48));
 EEPROM.write(108,(int)(payload[41]-48));
 EEPROM.write(109,(int)(payload[42]-48));
 EEPROM.write(110,(int)(payload[43]-48));
 }
    if ((char)payload[45] == 'S'){
if ((char)payload[47] == 'N'){sun=false;}

if ((char)payload[47] == 'D'){sun=true;}
 EEPROM.write(112,sun);
    }
     
 S = (((int)payload[45]-48)*1000+((int)payload[46]-48)*100+((int)payload[47]-48)*10+((int)payload[48]-48));
   
 EEPROM.commit();  
   snprintf (msg, MSG_BUFFER_SIZE, "MSG No. #%d recived",S);
   snprintf (msg, MSG_BUFFER_SIZE, "R1:%d R2:%d R3:%d R4:%d R5:%d R6:%03d T:%03d D:%04d LM:%d  #%ld ",R1,R2,R3,R4,R5,R6,T,LD,LM,MSG_NO);
   client.publish(Pub, msg);  
    yield();  }

void connectMqTT() {
  if (!client.connected()) {
    //Serial.print("Attempting MQTT connection...");
    String clientId = "RC"+ID;

     if (client.connect((char*) clientId.c_str())) {
        yield(); 
       client.publish(Pub, "slave is on");
      //Serial.print("\tMQTT Connected\n");
      client.subscribe(Sub);
     yield();    }
else {
      //Serial.println("failed to connect to mqtt"); 
      yield(); 
    }
  }
}
void http_forum_load(){
if (MDNS.begin("esp8266")) {
    //Serial.println("MDNS responder started");
    yield(); }

 server.on("/", handleRoot);
 server.on("/postform/", handleForm);
  server.begin();
  //Serial.println("HTTP server started");
  }
void setup() {
  EEPROM.begin(512);
  Serial.begin(115200);
  R1=EEPROM.read(101);
  R2=EEPROM.read(102);
  R3=EEPROM.read(103);
  R4=EEPROM.read(104);
  R5=EEPROM.read(105);
  R6=EEPROM.read(106);
  LD=(EEPROM.read(107)*1000)+(EEPROM.read(108)*100)+(EEPROM.read(109)*10)+(EEPROM.read(110));
  LM=EEPROM.read(111);
  sun=EEPROM.read(112);

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
   ////Serial.println("Failed to connect to MQTT server ; configuring a hot spot");
    //Serial.print("IP address: ");
    WiFi.softAPConfig(local_IP, gateway, subnet) ;
    //Serial.println(WiFi.softAPIP());

    WiFi.softAP("MQTT!RCID: "+ID);
    mq=2;
   mqtt_time=millis();
    http_forum_load();} 
}
 }
client.loop();

   if (WiFi.status() != WL_CONNECTED&&temo==0){  //Serial.println("Wifi disconnected .... begin the count down till restart");
    temo=millis();}
     if (!client.connected()&&temo==0){  //Serial.println("MqTT disconnected .... begin the count down till restart");
    temo=millis(); }
    if (client.connected()&&temo>0){ //Serial.println("MqTT Connected .... begin the count down till restart");
      temo=0; }
    
 if (millis()-temo>300000){
  
  //Serial.println();
  //Serial.println("i am restarting");
  ESP.restart();}


    if (chk==false && client.connected()){
   if (millis() - lastMsg > 2000) {
    lastMsg = millis();
    ++MSG_NO;
    snprintf (msg, MSG_BUFFER_SIZE, "R1:%d R2:%d R3:%d R4:%d R5:%d R6:%03d T:%03d D:%04d LM:%d  #%ld ",R1,R2,R3,R4,R5,R6,T,LD,LM,MSG_NO);
  
    //Serial.print("Publish message: ");
    //Serial.println(msg);
    client.publish(Pub, msg);
  }}
  
}
