#include<ESP8266WiFi.h>
int pir = 4 ;
char IR=A0;
const char* ssid = "Na7rawy Limited"; //your WiFi Name
const char* password = "Selim&Na7rawy";  //Your Wifi Password
int relay = 13;
int state = 4;
WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  delay(10);
 pinMode(pir,INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");}
  Serial.println("");
  Serial.println("WiFi connected");
  // Start the server
  server.begin();
  Serial.println("Server started");
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");} 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {return;}
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);}
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  // Match the request
  int state = 0 ;
  if (request.indexOf("/automatic") != -1){
    state = 0;} 
  if (request.indexOf("/Light=ON")  != -1){
    state = 1;}
  if (request.indexOf("/Light=OFF") != -1){
    state = 2;}
  if (state == 0){ if (analogRead(IR)<20){delay(1000);
      digitalWrite(relay, LOW);} 
  if (digitalRead(pir)==1){digitalWrite(relay, HIGH);}
   }
  delay(1);}
  if (state == 1){digitalWrite(relay,HIGH);}
  if (state == 2){digitalWrite(relay,LOW);}
// Set relay according to the request
//digitalWrite(relay, state);
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("Light state is now: ");
   if(state == 2) {
    client.print("automatic");}
   if(state == 1) {
    client.print("On");}
   if(state == 0) {
    client.print("off");}
  client.println("<br><br>");
  client.println("<a href=\"/automatic\"\"><button>automatic </button></a>");
  client.println("<a href=\"/Light=ON\"\"><button> On </button></a>");
  client.println("<a href=\"/Light=OFF\"\"><button> Off </button></a><br />"); 
  client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
