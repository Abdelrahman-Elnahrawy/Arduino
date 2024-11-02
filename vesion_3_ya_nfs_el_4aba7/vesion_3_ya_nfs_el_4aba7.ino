#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 5 //D1
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const char* ssid = "Na7rawy Limited";
const char* password = "Selim&Nahrawy751";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);
float t=0;
unsigned long lastMsg = 0;
unsigned long lastMsg1= 0;
unsigned long lastMsg2= 0;
unsigned long lastMsg3= 0;
int R1     =0;
int R2     =0;
int R3     =0;
int R4     =0;
int R5     =0;
int R6     =0;

int value  =0;
int value1 =0;
int value2 =0;
int value3 =0;
int S      =0;
int pir    =2; //D4
int button =4; //D2

int relay1=12; //D6
int relay2=13; //D7
int relay3=14; //D5
int relay4=15; //D8
int relay5 =0; //D3
int relay6=16; //D0

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

void callback(char* topic, char* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print(payload);
  }
  Serial.println();
 
if ((char)payload[0] == 'r'&&(char)payload[5] == '1'&&(char)payload[7] == 'n'){
  digitalWrite(relay1, HIGH);
  R1=1;
}
if ((char)payload[0] == 'r'&&(char)payload[5] == '1'&&(char)payload[7] == 'f'){
  digitalWrite(relay1, LOW);
  R1=0;
}




if ((char)payload[0] == 'r'&&(char)payload[5] == '2'&&(char)payload[7] == 'n'){
  digitalWrite(relay2, HIGH);
  R2=1;
}
if ((char)payload[0] == 'r'&&(char)payload[5] == '2'&&(char)payload[7] == 'f'){
  digitalWrite(relay2, LOW);
  R2=0;
}




if ((char)payload[0] == 'r'&&(char)payload[5] == '3'&&(char)payload[7] == 'n'){
  digitalWrite(relay3, HIGH);
  R3=1;
}
if ((char)payload[0] == 'r'&&(char)payload[5] == '3'&&(char)payload[7] == 'f'){
  digitalWrite(relay3, LOW);
  R3=0;
}



if ((char)payload[0] == 'r'&&(char)payload[5] == '4'&&(char)payload[7] == 'n'){
  digitalWrite(relay4, HIGH);
  R4=1;
}
if ((char)payload[0] == 'r'&&(char)payload[5] == '4'&&(char)payload[7] == 'f'){
  digitalWrite(relay4, LOW);
R4=0;
}



if ((char)payload[0] == 'r'&&(char)payload[5] == '5'&&(char)payload[7] == 'n'){
  digitalWrite(relay5, HIGH);
  R5=1;
}
if ((char)payload[0] == 'r'&&(char)payload[5] == '5'&&(char)payload[7] == 'f'){
  digitalWrite(relay5, LOW);
  R5=0;
}



if ((char)payload[0] == 'r'&&(char)payload[5] == '6'&&(char)payload[7] == 'n'){
  digitalWrite(relay6, HIGH);
  R6=1;
}
if ((char)payload[0] == 'r'&&(char)payload[5] == '6'&&(char)payload[7] == 'f'){
  digitalWrite(relay6, LOW);
  R6=0;
}
}
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe("zabolaa");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
     
      delay(5000);
    }
  }
}

void setup() {
  
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(pir   , INPUT);
  sensors.begin();
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
  sensors.requestTemperatures();

  t = sensors.getTempCByIndex(0);
  unsigned long now = millis();
 if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, " Temperature: %f  #%d",t, value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("esp8266/TEMP", msg);
  
  }
if (now - lastMsg1 > 1000&& digitalRead(pir)==HIGH) {
    lastMsg1 = now;
    ++value1;
    snprintf (msg, MSG_BUFFER_SIZE, "ALERT #%d", value1);
    Serial.print("Publish message: ");
    Serial.println(msg);
     Serial.println("esp8266/PIR");
    client.publish("esp8266/PIR", msg);
  }
  if (now - lastMsg2 > 700&& digitalRead(button)==HIGH) {
    lastMsg2 = now;
    ++value2;
    snprintf (msg, MSG_BUFFER_SIZE, "PRESS NO. #%d", value2);
    Serial.print("Publish message: ");
    Serial.println(msg);
     Serial.println("esp8266/BUTTON");
    client.publish("esp8266/BUTTON", msg);
  }
   if (now - lastMsg3 > 2000) {
    lastMsg3 = now;
    ++value3;
    snprintf (msg, MSG_BUFFER_SIZE, "R1:%d R2:%d R3:%d R4:%d R5:%d R6:%d #%d",R1,R2,R3,R4,R5,R6, value3);
    Serial.print("Publish message: ");
    Serial.println(msg);
     Serial.println("esp8266/feedback");
    client.publish("esp8266/feedback", msg);
  }
}
