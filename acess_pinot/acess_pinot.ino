
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

IPAddress local_IP(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);
void setup() {
  WiFi.softAPConfig(local_IP, gateway, subnet) ;
  delay(1000);
  WiFi.softAP("ESP help!!");
}

void loop() {
}
