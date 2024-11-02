
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


const char* WifiName="Na7rawy Limited";
const char* WifiPass="Selim&Nahrawy751";
String webPage,notice;

ESP8266WebServer server(80);

const char htmlPage[]PROGMEM=R"=====(
<!DOCTYPE html>
<html>
<body>
<h3>Electronic Notice Board </h3>
<FORM METHOD="POST"action="/postForm">
<input type="text" name="myText" value="Write your Notice...">
<input type="submit" value="Post Notice">
</form>
</body>
</html>
)=====";

void handlePostForm()
{
 webPage=htmlPage;
 notice=server.arg("myText");
 Serial.println("Text Received, contents:");
 Serial.println(notice);
 server.send(200,"text/html",webPage);
}

   void setup()
   {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.print("Connecting");
  WiFi.begin(WifiName,WifiPass);
  server.on("/postForm",handlePostForm);
  while(WiFi.status()!= WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    }
 Serial.println("");
 Serial.println("Wi-Fi Connected");
 Serial.println("IP Address is:");
 Serial.println(WiFi.localIP());
   Serial.println(notice);
server.begin();
Serial.println("HTTP Server Started");    
  // put your setup code here, to run once:
}


void loop() {
  server.handleClient();
  WiFiClient client = server.available();

}
