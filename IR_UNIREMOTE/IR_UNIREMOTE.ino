#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);




void handleForm() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
String USR= "";
String PASS="";
    //USR +=server.arg(0);
    //PASS +=server.arg(1);
   // eeprom=USR+"^"+PASS+"^";
   /* for(int n=0; n< eeprom.length();n++){
    yield(); 
  //EEPROM.write(n,eeprom[n]);}
  //EEPROM.commit();
    Serial.print("the user name is : ");
    Serial.println(USR);
     Serial.print("the user password is : ");
    Serial.println(PASS);
    server.send(200,"text/plain", "On the way");
    WiFi.softAPdisconnect (true);
    Serial.println("retry to connect");
   ESP.restart();}*/
    yield(); }
    
void handleRoot() {
  server.send(200, "text/html", postForms);
}

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

// Update these with values suitable for your network.

const char* WIFI_SSID = "Na7rawy Limited II";
const char* WIFI_PASS = "W--#pucr4br9dr44Ri6";
const char* mqtt_server = "broker.emqx.io";
IPAddress subnet (255,255,255,0);
IPAddress local_IP(192,168,4,22);
IPAddress gateway  (192,168,4,9);
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void http_forum_load(){
if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
    yield(); }

 server.on("/", handleRoot);
 server.on("/postform/", handleForm);
  server.begin();
  Serial.println("HTTP server started");}

  
void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("WiFi SSID:");
    Serial.println(WIFI_SSID);
  Serial.print("WiFi WIFI_PASSword:");
  Serial.println(WIFI_PASS);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID,WIFI_PASS);

//int WIFI_LOOP= true;


 for(unsigned long WIFI_CONNECTING_TIME=millis(); WiFi.status() != WL_CONNECTED;yield()) {
   /*   
      if(WIFI_LOOP==true){
        delay(1);
      Serial.print("Username:");  
        Serial.print(WIFI_SSID);
        Serial.println("");
      Serial.print("WIFI_Password:");
      Serial.println(WIFI_PASS);} 
    WIFI_LOOP=false;
    */
    if (millis()-WIFI_CONNECTING_TIME>7000){
    Serial.println("Failed to connect to wifi ; configuring a hot spot");
    Serial.print("IP address: ");
    WiFi.softAPConfig(local_IP, gateway, subnet) ;
    Serial.println(WiFi.softAPIP());
    WiFi.softAP("WiFi!IR_ID:");
    http_forum_load();
//WIFI_LOOP=true;
while(millis()-WIFI_CONNECTING_TIME<170000){
  server.handleClient();
  yield();
  }
    break;}
    
    if (WiFi.status() == WL_CONNECTED){
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());}
  }
}



void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
yield(); 


  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
  }
}
