#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
String  USR  = "Naa7rawy Limited";
String PASS  = "Selim&Nahrawy751";
String ssid;
String password;
ESP8266WebServer server(80);
IPAddress local_IP(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);
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
      WiFi.softAPConfig(local_IP, gateway, subnet) ;
     
    WiFi.begin(ssid,password);
    Serial.println("");
    delay(1000);
    for(int i=0; WiFi.status() != WL_CONNECTED;i++) {
    delay(500);
    Serial.print(".");
    if (i>15){delay(1000);
    Serial.println("configuring a hot spot");
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
    WiFi.softAP("ESP help!!");
    break;}
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(USR);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  }
  
  }


void handleForm() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
String USR= "";
String PASS="";
String ssid="";
String password="";
    ssid +=server.arg(0);
    password +=server.arg(1);
    Serial.print("the user name is : ");
    Serial.println(USR);
     Serial.print("the user password is : ");
    Serial.println(PASS);
    server.send(200,"text/plain", "On the way");
    delay(550);
    WiFi.softAPdisconnect (true);
    delay(1000);
    Serial.println("retry to connect");
   setup_wifi();}
}


void setup() {
  delay(1000);
  setup_wifi();
  Serial.begin(115200);
  // Wait for connection  
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);


 server.on("/postform/", handleForm);


  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
