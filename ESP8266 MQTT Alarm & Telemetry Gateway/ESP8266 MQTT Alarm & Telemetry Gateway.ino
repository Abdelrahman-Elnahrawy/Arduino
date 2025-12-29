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
String ID ="1";
const char* Pub = "ESP_Pub_1";
const char* Sub = "ESP_Sub_1";
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
bool R1     = 0;
bool R2     = 0;
bool R3     = 0;
bool R4     = 0;
bool R5     = 0;
int  R6     = 0;
int  MS     = 3; // motion sensor
int  relay1 = 4; 
int  relay2 = 5;  
int  relay3 = 0; 
int  relay4 = 2; 
int  relay5 =15; 
int  relay6 =16; 
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
 
  yield();
}
  EEPROM.commit();
  //Serial.println("a new wifi data is entered"); 
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
if((char)payload[23] == '1'){R5=1;}
  else  {R5=0;}
digitalWrite(relay5,R5);
EEPROM.write(105,R5);
} 
  if ((char)payload[25] == 'R'&&(char)payload[26] == '6'){
 R6 = ((int)payload[28]-48)*100+((int)payload[29]-48)*10+((int)payload[30]-48);
  if (R6<0){R6=0;
  digitalWrite(relay6,LOW);}
 if (R6>240){R6=256;
digitalWrite(relay6,HIGH);}
if(0<R6<240){
analogWrite (relay6,R6);}
EEPROM.write(106,R6);}
 if ((char)payload[35] == 'M'){ LM=0;
 EEPROM.write(111,LM);}
if ((char)payload[35] == 'S'){ LM=1;
 EEPROM.write(111,LM);}
if ((char)payload[35] == 'A'){ LM=2;
 EEPROM.write(111,LM);}
 
   if ((char)payload[0] == 'R'&&(char)payload[1] == '1'){
    if((char)payload[3] == '1'){R1=1; if (LM == 2){LM=1;}  }
    if((char)payload[3] == '0'){R1=0;  if (LM == 2){LM=1;} TtT=millis();}                                
digitalWrite(relay1,R1);
EEPROM.write(101,R1);



}
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
  pinMode(A0      ,  INPUT);
  pinMode(relay1  , OUTPUT);
  pinMode(relay2  , OUTPUT);
  pinMode(relay3  , OUTPUT);
  pinMode(relay4  , OUTPUT);
  pinMode(relay5  , OUTPUT);
  pinMode(relay6  , OUTPUT);
  pinMode(MS      ,  INPUT);
  pinMode(KP_1    ,  INPUT);
  pinMode(KP_2    ,  INPUT);
  pinMode(KP_3    ,  INPUT);
  EEPROM.begin(512);
  //Serial.begin(115200);
  R1=EEPROM.read(101);
  R2=EEPROM.read(102);
  R3=EEPROM.read(103);
  R4=EEPROM.read(104);
  R5=EEPROM.read(105);
  R6=EEPROM.read(106);
  LD=(EEPROM.read(107)*1000)+(EEPROM.read(108)*100)+(EEPROM.read(109)*10)+(EEPROM.read(110));
  LM=EEPROM.read(111);
  sun=EEPROM.read(112);
  digitalWrite(relay1,R1);
  digitalWrite(relay2,R2);
  digitalWrite(relay3,R3);
  digitalWrite(relay4,R4);
  digitalWrite(relay5,R5);
  analogWrite (relay6,R6);


  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  //http_forum_load();
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






if(millis() - temp_time > 30000){
temp_time=millis();
T=analogRead(A0);
}
//noInterrupts();


if(millis() - button_time > 500 ){

if(digitalRead(KP_1)||digitalRead(KP_2)||digitalRead(KP_3)){
  button_time = millis();
if(digitalRead(KP_1)==0  && digitalRead(KP_2)==0&& digitalRead(KP_3)==1){
  R3=!R3; 
       digitalWrite(relay3,R3);
     EEPROM.write(103,R3);
  /*
     R1=!R1;
     digitalWrite(relay1,R1);
     EEPROM.write(101,R1);
     LM=0;
     EEPROM.write(111,LM);*/}
if(digitalRead(KP_1)==0  && digitalRead(KP_2)==1&& digitalRead(KP_3)==0){

  LM=LM-1;
  if (LM<0){LM=2;}
 /* R2=!R2;   
     digitalWrite(relay2,R2);
     EEPROM.write(102,R2);*/}
if(digitalRead(KP_1)==0  && digitalRead(KP_2)==1&& digitalRead(KP_3)==1){
  if(R1==1){ TtT=millis();}
  R1=!R1;
  TtT=millis();
     digitalWrite(relay1,R1);
     EEPROM.write(101,R1);
      if (LM == 2){LM=1;}
     /*
       R3=!R3; 
       digitalWrite(relay3,R3);
     EEPROM.write(103,R3);*/}
if(digitalRead(KP_1)==1  && digitalRead(KP_2)==0&& digitalRead(KP_3)==0){
    R2=!R2;   
     digitalWrite(relay2,R2);
     EEPROM.write(102,R2);
  /*
  R4=!R4;   
     digitalWrite(relay4,R4);
     EEPROM.write(104,R4);*/}
if(digitalRead(KP_1)==1  && digitalRead(KP_2)==0&& digitalRead(KP_3)==1){
  R5=!R5;  
     digitalWrite(relay5,R5);
     EEPROM.write(105,R5);}
if(digitalRead(KP_1)==1  && digitalRead(KP_2)==1&& digitalRead(KP_3)==0){
  R6=R6+4; 
 button_time = button_time-690;   
  if (R6>255){R6=0;}
  if (R6<0){R6=256;}
  analogWrite(relay6,R6);
  EEPROM.write(106,R6)  ;
  if(R6==0){ button_time = button_time+1000;}
   }
  if(digitalRead(KP_1)==1  && digitalRead(KP_2)==1&& digitalRead(KP_3)==1){LM=LM-1;
  if (LM<0){LM=2;}
   EEPROM.write(111,LM);}
   EEPROM.commit();}  
}
 if (LM == 1){
 if(digitalRead(MS)==LOW&&!sun&&millis()-TtT>5000){R1=HIGH;}
  digitalWrite(relay1,R1);}
          if (LM == 2){
 if (digitalRead(MS)==LOW&&!sun) {
    T1= millis();
    R1=HIGH;
     }
    if (millis() - T1> LD*1000) {R1=0;}
    digitalWrite(relay1,R1); }
// interrupts();


        
if(digitalRead(MS)==LOW&&millis() - alrm > 1500){
   alrm = millis();
  client.publish(Pub,"alarm");
  }
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
