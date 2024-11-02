
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
boolean mod=0 ;
int button;
const char* ssid = "Na7rawy Limited";
const char* password = "Selim&Nahrawy751";
const char* mqtt_server = "192.168.1.123";
const char* mqtt_username = "zabolaa";
const char* mqtt_password = "zabolaa";
const char* Pub = "pub";
const char* Sub = "sub";
WiFiClient espClient;
PubSubClient client(espClient);
float t=0;
unsigned long lastMsg    = 0;
unsigned long lastMsg_pir= 0;
unsigned long T1         = 0;
unsigned long button_time= 0;
unsigned long temp_time= 0;
bool R1      =0;
bool R2      =0;
bool R3      =0;
bool R4      =0;
bool R5      =0;
int  R6      =0;
int  value   =0;
int  value1  =0;
int  S       =0;
int  pir     =2; //D4
int  relaymod=4; //D2
int  relay1 =12; //D6
int  relay2 =13; //D7
int  relay3 =14; //D5
int  relay4 =15; //D8
int  relay5 =0 ; //D3
int  relay6 =16; //D0

#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
    Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();



if ((char)payload[0] == 'R'&&(char)payload[1] == '1'){
if((char)payload[3] == '1'){R1=1;}
  else  {R1=0;}     
digitalWrite(relay1,R1); }    

if ((char)payload[5] == 'R'&&(char)payload[6] == '2'){
if((char)payload[8] == '1'){R2=1;}
else  { R2=0;}
digitalWrite(relay2,R2);}


if ((char)payload[10] == 'R'&&(char)payload[11] == '3'){
if((char)payload[13] == '1'){R3=1;}
  else  {R3=0;}
digitalWrite(relay3,R3); }   
if ((char)payload[15] == 'R'&&(char)payload[16] == '4'){
if((char)payload[18] == '1'){R4=1;}
  else  {R4=0;}
digitalWrite(relay4,R4);}    
if ((char)payload[20] == 'R'&&(char)payload[21] == '5'){
if((char)payload[23] == '1'){R5=1;}
  else  {R5=0;}
digitalWrite(relay5,R5);} 
  if ((char)payload[25] == 'R'&&(char)payload[26] == '6'){
 R6 = ((int)payload[28]-48)*100+((int)payload[29]-48)*10+((int)payload[30]-48);
 analogWrite (relay6,R6);} 

 }

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "zabolaa";

     if (client.connect((char*) clientId.c_str(), mqtt_username, mqtt_password)) {
       client.publish(Pub, "hello world");
      Serial.print("\tMTQQ Connected");
      client.subscribe(Sub);
    }
else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
     
      delay(5000);
    }
  }
}

void setup() {
  
  pinMode(relay1  , OUTPUT);
  pinMode(relay2  , OUTPUT);
  pinMode(relay3  , OUTPUT);
  pinMode(relay4  , OUTPUT);
  pinMode(relay5  , OUTPUT);
  pinMode(relay6  , OUTPUT);
  pinMode(relaymod, OUTPUT);
  pinMode(pir     ,  INPUT);
  
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
}

void loop() {
if (!client.connected()) {
    reconnect();
  }
client.loop();
delay(10);
  unsigned long now = millis();
if(now - temp_time > 600000){
mod=1;
temp_time=now;
digitalWrite(relaymod,HIGH);}
 if (mod==0){
button =analogRead(A0);}
else {
  delay(10);
  t=analogRead(A0)/10;
  mod=0;
  digitalWrite(relaymod,LOW);}

 if(now - button_time > 700 && button<1024){
  button_time = now;
if(button>=400 && button<500 ){R1=!R1;  
     digitalWrite(relay1,R1);}
if(button> 150 && button<300 ){R2=!R2;   
     digitalWrite(relay2,R2);}
if(button> 600 && button<700 ){R3=!R3;  
     digitalWrite(relay3,R3);}
if(button> 750 && button<900 ){R4=!R4;   
     digitalWrite(relay4,R4);}
if(button> 0   && button<100 ){R5=!R5;  
     digitalWrite(relay5,R5);}
if( button>900 && button<1020){R6=R6+1; 
 button_time = button_time-690;   
  if (R6>256){R6=0;}
  if (R6<0  ){R6=0;}
  analogWrite(relay6,R6);
  if(R6==0){delay(1000);}
   }
   }           
   if (now - lastMsg_pir > 2000 && digitalRead(pir)==1) {
    lastMsg_pir = now;
    ++value1;
    snprintf (msg, MSG_BUFFER_SIZE, "PIR is HIGH #%d",value1);

    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(Pub, msg);
  }
   if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "R1:%d R2:%d R3:%d R4:%d R5:%d R6:%d T:%f  #%d ",R1,R2,R3,R4,R5,R6,t,value);

    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(Pub, msg);
  }
}
