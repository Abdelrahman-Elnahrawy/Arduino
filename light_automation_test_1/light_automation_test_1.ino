#include<ESP8266WiFi.h>
const char* ssid = "Na7rawy Limited"; //your WiFi Name
const char* password = "Selim&Nahrawy751";  //Your Wifi Password
int lights_1 = 5  ;
int lights_2 = 10  ;
int button_1 = 14 ;
int pir=4;
char IR=A0;
int state = 2; 
String request;
WiFiServer server(80);
void setup() {
   Serial.begin(115200);
  delay(10);
  pinMode(lights_1, OUTPUT);
  pinMode(lights_2, OUTPUT);
  pinMode(button_1, INPUT);
  pinMode(pir, INPUT);
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
  WiFiClient client = server.available();
  //if (!client) {return;}
  // Wait until the client sends some data
  //Serial.println("new client");
  //while(!client.available()){delay(1);}
    request =String  (client.readStringUntil('\r'));
    Serial.print("the request is :");
 Serial.println(request);
     Serial.print("END");
    //request.length()
  /* if (request[4]=='/'){
    for (int nI = 0;request[nI] != '#'; nI++){
   Serial.print(request[nI]);
}
Serial.println();}*/
 // client.flush();
  // Match the request
  int state = 0 ;
  if (request.indexOf("/automatic") != -1){
    state = 2;} 
  if (request.indexOf("/Light=ON")  != -1){
    state = 1;}
  if (request.indexOf("/Light=OFF") != -1){
    state = 0;}
  if (state==0)  {
digitalWrite(lights_1, LOW);
  }
   if(state==1){
    digitalWrite(lights_1, HIGH);
  }
if (state==2){
  if (analogRead(IR)<10)  {digitalWrite(lights_1, LOW);} 
  else {digitalWrite(lights_1, HIGH);}
 // if (digitalRead(pir)==1){digitalWrite(lights_1, HIGH);}
 }
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
    client.println(analogRead(IR));
      client.println("<br><br>");
    client.println(digitalRead(pir));
  client.println("<br><br>");
  client.println("<a href=\"/automatic\"\"><button>automatic </button></a>");
  client.println("<a href=\"/Light=ON\"\"><button> On </button></a>");
  client.println("<a href=\"/Light=OFF\"\"><button> Off </button></a><br />"); 
  client.println( " <input type=\"text\" name=\"myText\" value=\"Write your Notice...\">");
  if (state==2){client.println("<meta http-equiv=\"refresh\" content=\"0.1\" />");}

  client.println("</html>");
  
}
