#include <ESP8266WiFi.h>
#include <time.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
ESP8266WebServer server(80);
const unsigned int MAX_MESSAGE_LENGTH = 100;
IPAddress local_IP(192,168,1,124);
IPAddress gateway  (192,168,4,9);
IPAddress subnet (255,255,255,0);
String eeprom;
String ID ="TsesT";
const char* Pub = "ESP_Pub_TsesT";
const char* Sub = "ESP_Sub_TsesT";
String USR   ;
String PASS  ;
int    f     ;
int    mq=1  ;
const char* mqtt_server = "NA7RAWY_PC.local";
const char* mqtt_username =   "home" ;
const char* mqtt_password =   "me5afa4e5a" ;
WiFiClientSecure espClient;
PubSubClient client;
int wifierror = 2;
int mqtterror = 5;
int htspt     = 4;
int MSG_NO=0;
int  T=0    ;
int LDR=0   ;
bool LM=0   ;
int  S=0    ;
int T1=0    ;
int LD=10000; 
char incomingByte = 0; 
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
bool R6     = 0;
bool R7     = 0;
bool R8     = 0;
bool R9     = 0;
bool R10    = 0;
bool R11    = 0;
int  PWMD0    =0;
int  PWMD1    =0;
int  PWMD2    =0;
int  PWMA0    =0;
int  PWMA1    =0;
int  PWMA2    =0;
int  pn     =0 ; //password begin byte in the eebrom
bool   chk = 0 ; //wifi connection info / if 1 hot spot mode if 0 then wifi mode.
int  HS =  13   ;   // hotspot switch //D7
#define MSG_BUFFER_SIZE  (160)
char msg[MSG_BUFFER_SIZE];
 String postForms ="<!DOCTYPE html>\
<!DOCTYPE html>\
<html>\
<head>\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
<style>\
body {font-family: Arial, Helvetica, sans-serif;}\
.vertical-center {margin: 0;position: absolute; top: 50%;-ms-transform: translateY(-50%);transform: translateY(-50%);}\
input[type=text], input[type=password] {width: 100%;padding: 12px 20px;margin: 8px 0; display: inline-block;border: 1px solid #ccc;box-sizing: border-box;}\
button { background-color: #04AA6D;color: white;padding: 14px 20px;margin: 8px 0; border: none;cursor: pointer; width: 100%;}\
button:hover {opacity: 0.8;}\
.cancelbtn { width: auto;padding: 10px 18px;background-color: #f44336;}\
.container {padding: 16px;}\
span.psw {float: right;padding-top: 16px;}\
.modal { display: none; position: fixed; z-index: 1; left: 0;top: 0; width: 100%;  height: 100%; overflow: auto; background-color: rgb(0,0,0); \
  background-color: rgba(0,0,0,0.4); }\
.modal-content { background-color: #fefefe; margin: 5% auto 15% auto;border: 1px solid #888;width: 80%;}\
h1 {font-family: 'Times New Roman', serif;  }\
.close {position: absolute;right: 25px;top: 0;color: #000;font-size: 35px;font-weight: bold;}\
.close:hover,\
.close:focus {color: red;cursor: pointer;}\
.animate {-webkit-animation: animatezoom 0.6s;animation: animatezoom 0.6s}\
@-webkit-keyframes animatezoom {from {-webkit-transform: scale(0)}  to {-webkit-transform: scale(1)}} \
@keyframes animatezoom {\
  from {transform: scale(0)} to {transform: scale(1)}\
}\
@media screen and (max-width: 300px) {\
  span.psw {display: block;float: none;}\
  .cancelbtn { width: 100%;}}\
</style>\
</head>\
<body>\
<center> \
<h1>Imhotep</h1>\
<p>Wifi entry mode :D </p>\
<button onclick=\"document.getElementById('id01').style.display='block'\" style=\"width:auto; margin: 5%;\">change Wi-fi data</button>\
<div id=\"id01\" class=\"modal\">\
<form class=\"modal-content animate\"  method=\"post\"  enctype=\"application/x-www-form-urlencoded\" action=\"/postform/\" >\
    <div class=\"imgcontainer\">\
            <span onclick=\"document.getElementById('id01').style.display='none'\" class=\"close\" title=\"Close Modal\">&times;</span>\
    </div>\
    <div class=\"container\">\
      <label for=\"uname\"><b>WiFi ID</b></label>\
      <input type=\"text\" placeholder=\"Enter network Username\" name=\"uname\" value=\"SSID\" required>\
      <label for=\"psw\"><b>Password</b></label>\
      <input type=\"password\" placeholder=\"Enter Password\" name=\"psw\" value=\"PASSWORD\" required> \
      <button type=\"submit\">Submit</button>\
    </div> \
    <div class=\"container\" style=\"background-color:#f1f1f1\">\
      <button type=\"button\" onclick=\"document.getElementById('id01').style.display='none'\" class=\"cancelbtn\">Cancel</button>\
    </div>\
  </form>\
</div>\
<script>\
var modal = document.getElementById('id01');\
window.onclick = function(event) {if (event.target == modal) {modal.style.display = \"none\";}}\
</script>\
<button onclick=\"document.getElementById('id02').style.display='block'\"  margin: 5%; style=\"width:auto;\">Why am i here ?!</button>\
<div id=\"id02\" class=\"modal\">\
<form class=\"modal-content animate\"  method=\"post\"  enctype=\"application/x-www-form-urlencoded\" action=\"/postform/\" >\
    <div class=\"imgcontainer\">\
      <span onclick=\"document.getElementById('id02').style.display='none'\" class=\"close\" title=\"Close Modal\">&times;</span>\
    </div>\
<h1>Imhotep</h1>\
    <div class=\"container\" style=\"background-color:#f1f1f1\">\
      <button type=\"button\" onclick=\"document.getElementById('id02').style.display='none'\" class=\"cancelbtn\">okay</button>\
    </div>\
  </form>\
</div>\
<p>Imhotep contact information and our site link</p>\
</center>\
</body>\
</html>";
static const char *fingerprint PROGMEM = "D1 A3 E7 C1 EB FE 61 DC EA EE D5 A6 80 A1 4C DD 62 F0 FF BD";

// Set x509 CA root (must match server cert)
/*
const char ca_cert[] PROGMEM = R"EOF("
-----BEGIN CERTIFICATE-----
MIIDsTCCApmgAwIBAgIUEsfM7Eau97cu1g/GUNbYVu7hDSUwDQYJKoZIhvcNAQEL
BQAwaDELMAkGA1UEBhMCRUcxDjAMBgNVBAgMBUNhaXJvMQ4wDAYDVQQHDAVDYWly
bzERMA8GA1UECgwIN2Ftb2tzaGExETAPBgNVBAsMCDdhbW9rc2hhMRMwEQYDVQQD
DApob21lYXNzaXN0MB4XDTIxMDkwMjE1MDAyOFoXDTIyMDkwMjE1MDAyOFowaDEL
MAkGA1UEBhMCRUcxDjAMBgNVBAgMBUNhaXJvMQ4wDAYDVQQHDAVDYWlybzERMA8G
A1UECgwIN2Ftb2tzaGExETAPBgNVBAsMCDdhbW9rc2hhMRMwEQYDVQQDDApob21l
YXNzaXN0MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAwgUbrLUzxj2a
AiBAn3NjGWweXO8ROj4ZsLssiXMqscPhRWXJP2XVdXcENL58UUd9jGXt2lagwGSk
6XIqRJj1PNlQLxqokCVBF5UGIdEr4E2QlEJqN6HbUMYmvdeznTVIk3hEBiHIr/EX
cEBN911ZzbBuaxL141g1D3ML4dwtOkd41xpmbDuxXDmPebC3ArTo9bBgbO3BhPV+
uPR5CMa4SKq6fjtoslOTvVKkeWPILrRzTjCZlwiw6U7F8FkNXREU87tkhl9CjcCC
3kfNmcsr5LtrpT3eNW3uDQM61FIIflHMXemkc7XbvDjSrmc/RxNqO97nY0If09oh
eq4T2P1GAwIDAQABo1MwUTAdBgNVHQ4EFgQU2pnLhl5fRXVs0sdVxd2N+0NPX+4w
HwYDVR0jBBgwFoAU2pnLhl5fRXVs0sdVxd2N+0NPX+4wDwYDVR0TAQH/BAUwAwEB
/zANBgkqhkiG9w0BAQsFAAOCAQEAVYNYLbJI55tXL4OW2NwZcgnCgXgA0VL9Qps8
2RMcYre9+Ib8DuzfJHLo5lBQVRfqXAQYztJwG3CjlQn4G3O1k4DiBOWBKrwF3dg3
P/ZLZknMFtfi5r6qbqDPZPqeOFiCiXOuwzKflcTV6PSHrJENJD1fidwWx4x/APy/
k0vR/ZdDgkeAG721+CxBht8cRGeLHOH5kBRbVSH210Nx0L1utPVB8Fxd02+XUbDd
XjJ7TwVml1hYb7b0f/2C9sswUJmhKtzBnkxDV278uBXdkqOGbtdy5j/wknF17LHA
nFHZ3VGc+R2iYvSnbgH0r/csnWYFJM0UqSs4BvKzUBCNUVBk4Q==
-----END CERTIFICATE-----
")EOF";

static const char client_cert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIC3DCCAcQCFDgnf6Mz/RJuIbDY5NDNSi3R1WxkMA0GCSqGSIb3DQEBCwUAMGgx
CzAJBgNVBAYTAkVHMQ4wDAYDVQQIDAVDYWlybzEOMAwGA1UEBwwFQ2Fpcm8xETAP
BgNVBAoMCDdhbW9rc2hhMREwDwYDVQQLDAg3YW1va3NoYTETMBEGA1UEAwwKaG9t
ZWFzc2lzdDAeFw0yMTA5MDIxNTE0MzlaFw0yMjA5MDIxNTE0MzlaMHExCzAJBgNV
BAYTAkVHMQ4wDAYDVQQIDAVDYWlybzEOMAwGA1UEBwwFQ2Fpcm8xGDAWBgNVBAoM
DzdhbW9rc2hhIENsaWVudDERMA8GA1UECwwIN2Ftb2tzaGExFTATBgNVBAMMDGNs
aWVudC5sb2NhbDCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAy1RUlUNsXJhR
mxXKWtHu8SUnTxhnlSRdPKF6yp3Qrnwhm8omPqlBf6CdraI7GHeRU76kXo3PiiLq
xHb8DQtm/XDTKAqSVRxp/zlgbJWPqT0YJLcU/2HKPSmtWcXNHCzYa/TsUsGFf4qY
J9duxtR33pKTJBveOP229Y+DgIfiVRECAwEAATANBgkqhkiG9w0BAQsFAAOCAQEA
mKbUs4Z8B8kigSu4xiVhubpt/hsCkc90GzRWQpJK7oYTKIspfVxYKB955dbThg0G
t5MzEaNKOeSRAePFfjE6WIdlhVz4T96MuKMGiK24dLKbtB2MQ9mSzqS4XEwB3o5T
OIj4/bIg1vugM+tYoSftM11cLHypzUgq4BFyDTCij05vzC9H6gKzkKY4iGO8zKFa
892Obzq5cBC810y/W6kJcaCJB7yPhMUpcZ3PTyE+f1ZLkpMLgcQSAHxr9/D/XQCj
2UuHH9vcYFBaU2x/Lv6hE5ZIQ98cIZFUHrtr/Z4woDYn8psFZYElvF1dJD87PRTb
6AWWiWK0N9JwoN/Pz7IX8A==
-----END CERTIFICATE-----
)EOF";

static const char client_key[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
Proc-Type: 4,ENCRYPTED
DEK-Info: DES-EDE3-CBC,2C3CC9021775CC04

j9MGNxzmrMvNBl7mEWfupnWzUwSwodsxU9x9vkGCHO31JMPqQdvWAONjFxzIuxGK
UtqjertkWaiuZVh4pQWPH6IUKRIqOva8Mldn809czWiDFdARyKTNweOG0CZazm60
by/oxbXSyVH6akl3UrVwZjYocmPvEYcbcP6Eu9QiKSHiz/FLKC/kti+1R/zDYyuE
pZerYqbrWI4sNSDQkjdiKo2GPWOFhsL3/VjBr0EmleNBXuZZm9FTya37RP97JH7j
l9VPKwAekV8LFS+8KWbmNvWj0gBrMJgyk6iWsZurJvhE+ur+Ui4V+EKbd3R0MMrZ
Gv2W0MkS5IPXVsc/w1VM5c1voPv3fylJq4VPUtlx7qgYmu4vOx2UHkcUD3cxUQfZ
NsvId3MTA8hoZi0V5/Yrpyx3f/yIbPx4LwyPE6GWyTFU19T4kRq27kbwLVuirdbr
IRK10R5Byh6eUE/iuVsk12wDYRVsigU7xK35OWM+p+XVrJofMPXXE7rHYWexCtDy
Ypgzcy+8yNlc8n0K1Se7jLcaI2tTf0yV2ji9898T7OHjE/91mmO3z/ASZBmWk1jN
rjywputCV5+bcQCNsd4G4vhB8xHOeIpjHLlNWZSgqIzS/9zrjwj8JbOlIAGsGNmt
ZHtAP8EDNwJFFTBQOh2W8NGrb4lRPZ04rUH6btmkgzMnINd119mRznXSkMD1g2Nf
7rWpbzSN+TtEQwLNc9yxbrOLl75yntALDhy7d/UgedS8n/WVKvmyWkMpaP2dbBjE
5nkANNYcJistYkX3BelyiPQCfY2vmrSn+AL5Exr9w1rSvLHW3X/jmw==
-----END RSA PRIVATE KEY-----
)KEY";

BearSSL::X509List *serverTrustedCA = new BearSSL::X509List(ca_cert);

BearSSL::X509List *client_crt = new BearSSL::X509List(client_cert);
BearSSL::PrivateKey *key = new BearSSL::PrivateKey(client_key);
*/
void handleRoot() {
  yield();
  server.send(200, "text/html", postForms);
}
void hotspot(){yield(); 
     WiFi.softAPConfig(local_IP, gateway, subnet) ;
    WiFi.softAP("WiFi!RCID: "+ID); 
}
void setup_wifi(){
  yield(); 
    Serial.println();
  Serial.println("trying to connect to wifi");
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
  }
void handleForm() {
String USR= "";
String PASS="";
    USR +=server.arg(0);
    PASS +=server.arg(1);
    eeprom=USR+"^"+PASS+"^";
    for(int n=0; n< eeprom.length();n++){
    yield(); 
  EEPROM.write(n,eeprom[n]);}
  EEPROM.commit();
    server.send(200,"text/plain", "On the way");
    yield(); 
    WiFi.softAPdisconnect (true); }


    
void callback(char* topic, byte* payload, unsigned int length) {

if ((char)payload[0] == '~'){
  for (int n=1;payload[n]!='~';n++){
  EEPROM.write(n-1,(char)payload[n]);
  yield();
}
  EEPROM.commit();
  ESP.restart();
}
if ((char)payload[1] == '0'){
if((char)payload[3] == '1'){R0=1;}
else  { R0=0;}
EEPROM.write(100,R0);
Serial.print("R0:");
Serial.println(R0);
}


if ((char)payload[1] == '1' && (char)payload[2] == ':'){
if((char)payload[3] == '1'){R1=1;}
else  { R1=0;}
EEPROM.write(101,R1);
Serial.print("R1:");
Serial.println(R1);
}
if ((char)payload[1] == '2' && (char)payload[2] == ':'){
if((char)payload[3] == '1'){R2=1;}
else  { R2=0;}
EEPROM.write(102,R2);
Serial.print("R2:");
Serial.println(R2);
}
if ((char)payload[1] == '3' && (char)payload[2] == ':'){
if((char)payload[3] == '1'){R3=1;}
else  { R3=0;}
EEPROM.write(103,R3);
Serial.print("R3:");
Serial.println(R3);
}
if ((char)payload[1] == '4' && (char)payload[2] == ':'){
if((char)payload[3] == '1'){R4=1;}
else  { R4=0;}
EEPROM.write(104,R4);
Serial.print("R4:");
Serial.println(R4);
}
if ((char)payload[1] == '5' && (char)payload[2] == ':'){
if((char)payload[3] == '1'){R5=1;}
else  { R5=0;}
EEPROM.write(105,R5);
Serial.print("R5:");
Serial.println(R5);
}
if ((char)payload[1] == '6' && (char)payload[2] == ':'){
if((char)payload[3] == '1'){R6=1;}
else  { R6=0;}
EEPROM.write(106,R6);
Serial.print("R6:");
Serial.println(R6);
}
if ((char)payload[1] == '7' && (char)payload[2] == ':'){
if((char)payload[3] == '1'){R7=1;}
else  { R7=0;}
EEPROM.write(107,R7);
Serial.print("R7:");
Serial.println(R7);
}
if ((char)payload[1] == '8' && (char)payload[2] == ':'){
if((char)payload[3] == '1'){R8=1;}
else  { R8=0;}
EEPROM.write(108,R8);
Serial.print("R8:");
Serial.println(R8);
}
if ((char)payload[1] == '9' && (char)payload[2] == ':'){
if((char)payload[3] == '1'){R9=1;}
else  { R9=0;}
EEPROM.write(101,R9);
Serial.print("R9:");
Serial.println(R9);
}
if ((char)payload[1] == '1' && (char)payload[2] == '0'){
if((char)payload[4] == '1'){R10=1;}
else  { R10=0;}
EEPROM.write(110,R10);
Serial.print("R10:");
Serial.println(R10);
}
if ((char)payload[1] == '1' && (char)payload[2] == '1'){
if((char)payload[4] == '1'){R11=1;}
else  { R11=0;}
EEPROM.write(111,R11);
Serial.print("R11:");
Serial.println(R11);
}


//PWMD0:
if ((char)payload[1] == 'W' && (char)payload[3] == '0'&& (char)payload[4] == ':'){
PWMD0 = ((int)payload[5]-48)*100+((int)payload[6]-48)*10+((int)payload[7]-48);
  if (PWMD0<0 ){PWMD0=0;}
 if (PWMD0>240){PWMD0=255;
 Serial.print("PWMD0:");
Serial.println(PWMD0);}
EEPROM.write(112,PWMD0);
}
if ((char)payload[1] == 'W' && (char)payload[3] == '1'&& (char)payload[4] == ':'){
PWMD1 = ((int)payload[5]-48)*100+((int)payload[6]-48)*10+((int)payload[7]-48);
  if (PWMD1<0 ){PWMD1=0;}
 if (PWMD1>240){PWMD1=255;}
 Serial.print("PWMD1:");
Serial.println(PWMD1);
EEPROM.write(113,PWMD1);
}
if ((char)payload[1] == 'W' && (char)payload[3] == '2'&& (char)payload[4] == ':'){
PWMD2 = ((int)payload[5]-48)*100+((int)payload[6]-48)*10+((int)payload[7]-48);
  if (PWMD2<0 ){PWMD2=0;}
 if (PWMD2>240){PWMD2=255;}
 Serial.print("PWMD2:");
Serial.println(PWMD2);
EEPROM.write(114,PWMD2);
}
if ((char)payload[1] == 'W' && (char)payload[3] == '3'&& (char)payload[4] == ':'){
PWMA0 = ((int)payload[5]-48)*100+((int)payload[6]-48)*10+((int)payload[7]-48);
  if (PWMA0<0 ){PWMA0=0;}
 if (PWMA0>240){PWMA0=255;}
 Serial.print("PWMA0:");
Serial.println(PWMA0);
EEPROM.write(115,PWMA0);
}
if ((char)payload[1] == 'W' && (char)payload[3] == '4'&& (char)payload[4] == ':'){
PWMA1 = ((int)payload[5]-48)*100+((int)payload[6]-48)*10+((int)payload[7]-48);
  if (PWMA1<0 ){PWMA1=0;}
 if (PWMA1>240){PWMA1=255;}
 Serial.print("PWMA1:");
Serial.println(PWMA1);
EEPROM.write(116,PWMA1);
}
if ((char)payload[1] == 'W' && (char)payload[3] == '5'&& (char)payload[4] == ':'){
PWMA2 = ((int)payload[5]-48)*100+((int)payload[6]-48)*10+((int)payload[7]-48);
  if (PWMA2<0 ){PWMA2=0;}
 if (PWMA2>240){PWMA2=255;}
 Serial.print("PWMA2:");
Serial.println(PWMA2);
EEPROM.write(117,PWMA2);
}

 if ((char)payload[0] == 'L'&&(char)payload[1] == 'M'){
if ((char)payload[3] == '0'){ LM=0;}
if ((char)payload[3] == '1'){ LM=1;}
  Serial.print("LM:");
Serial.println(LM);
 EEPROM.write(118,LM);
 }
  if ((char)payload[0] == 'D'){
 LD = ((int)payload[2]-48)*1000+((int)payload[3]-48)*100+((int)payload[4]-48)*10+((int)payload[5]-48);
 EEPROM.write(119,(int)(payload[40]-48));
 EEPROM.write(120,(int)(payload[41]-48));
 EEPROM.write(121,(int)(payload[42]-48));
 EEPROM.write(122,(int)(payload[43]-48));
 }    
 S = (((int)payload[45]-48)*1000+((int)payload[46]-48)*100+((int)payload[47]-48)*10+((int)payload[48]-48));
 EEPROM.commit();  
  // snprintf (msg, MSG_BUFFER_SIZE, "MSG No. #%d recived",S);
   //snprintf (msg, MSG_BUFFER_SIZE, "R1:%d R2:%d R3:%d R4:%d R5:%d R6:%03d T:%03d D:%04d LM:%d  #%ld ",R1,R2,R3,R4,R5,R6,T,LD,LM,MSG_NO);
  // Serial.println(msg);
 client.publish(Pub, msg);  
    yield();  }
void connectMqTT() {
delay(2000);
  if (!client.connected()) {
    //Serial.print("Attempting MQTT connection...");
    String clientId = "RC"+ID;
     if (client.connect((char*) clientId.c_str(),mqtt_username,mqtt_password)) {
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
if (!MDNS.begin("esp8266")) {
    yield(); }
 server.on("/", handleRoot);
 server.on("/postform/", handleForm);
  server.begin();
    MDNS.addService("http", "tcp", 80);
  }
void setup() { 

MDNS.begin("esp8266");
pinMode(HS,INPUT);
pinMode(wifierror,OUTPUT);
pinMode(mqtterror,OUTPUT);
pinMode(htspt    ,OUTPUT);
  EEPROM.begin(512);
  Serial.begin(9600);
  R1=EEPROM.read(101);
  R2=EEPROM.read(102);
  R3=EEPROM.read(103);
  R4=EEPROM.read(104);
  R5=EEPROM.read(105);
  R6=EEPROM.read(106);
  R7=EEPROM.read(107);
  R8=EEPROM.read(108);
  R9=EEPROM.read(109);
 R10=EEPROM.read(110);
 R11=EEPROM.read(111);
 PWMD0=EEPROM.read(112);
 PWMD1=EEPROM.read(113);
 PWMD2=EEPROM.read(114);
 PWMA0=EEPROM.read(115);
 PWMA1=EEPROM.read(116);
 PWMA2=EEPROM.read(117);
 LM  =EEPROM.read(118);
 LD=(EEPROM.read(119)*1000)+(EEPROM.read(120)*100)+(EEPROM.read(121)*10)+(EEPROM.read(122));
 if (digitalRead(HS)== HIGH){
   setup_wifi();
   client.setClient(espClient);
   espClient.setFingerprint(fingerprint);
   /*
   delay(11000);
  WiFi.setAutoReconnect(true);
 delay(1000);
  Serial.println("connected wifi");
  espClient.setTrustAnchors(serverTrustedCA);
  delay(1000);
  Serial.println("added CA trust");
 // espClient.setClientRSACert(client_crt, key);
  delay(1000);
  Serial.println("added client crt");

  time_t now = time(nullptr);
  delay(1000);
  Serial.println("got time now");
  espClient.setX509Time(now);
  delay(1000);
  Serial.println("creating client");
  
  
  delay(1000);
  Serial.println("client created");
*/
  
  connectMqTT();
  Serial.println("connecting to MQTT");
  client.setServer(mqtt_server, 8883);
  delay(1000);
  client.setCallback(callback); 
  chk = true ;
    digitalWrite(htspt,LOW);
    
 }
else{
  hotspot ();
    if (!MDNS.begin("esp8266")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  http_forum_load();
  chk = false ;
  digitalWrite(htspt,HIGH);
    Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

}
 
void loop() { //###############################################################################################################################################

 
  if (millis() - lastMsg > 2000) {
    lastMsg = millis();
    ++MSG_NO;
    snprintf (msg, MSG_BUFFER_SIZE, "me5a fa4e5a");
  
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(Pub, msg);
  }
 
 while (Serial.available() > 0)
 {
   static char message[MAX_MESSAGE_LENGTH];
   static unsigned int message_pos = 0;
   char inByte = Serial.read();
   if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
   { message[message_pos] = inByte;
     message_pos++;}
   else
   { message[message_pos] = '\0';
if ((char)message[1] == '0'){
if((char)message[3] == '1'){R0=1;}
else  { R0=0;}
EEPROM.write(100,R0);
  snprintf (msg, MSG_BUFFER_SIZE, "R0:%d",R0);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}
if ((char)message[1] == '1' && (char)message[2] == ':'){
if((char)message[3] == '1'){R1=1;}
else  { R1=0;}
EEPROM.write(101,R1);
  snprintf (msg, MSG_BUFFER_SIZE, "R1:%d",R1);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}

if ((char)message[1] == '2' && (char)message[2] == ':'){
if((char)message[3] == '1'){R2=1;}
else  { R2=0;}
EEPROM.write(102,R2);
  snprintf (msg, MSG_BUFFER_SIZE, "R2:%d",R2);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}

if ((char)message[1] == '3' && (char)message[2] == ':'){
if((char)message[3] == '1'){R3=1;}
else  { R3=0;}
EEPROM.write(103,R3);
  snprintf (msg, MSG_BUFFER_SIZE, "R3:%d",R3);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}

if ((char)message[1] == '4' && (char)message[2] == ':'){
if((char)message[3] == '1'){R4=1;}
else  { R4=0;}
EEPROM.write(104,R4);
  snprintf (msg, MSG_BUFFER_SIZE, "R4:%d",R4);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}

if ((char)message[1] == '5' && (char)message[2] == ':'){
if((char)message[3] == '1'){R5=1;}
else  { R5=0;}
EEPROM.write(105,R5);
  snprintf (msg, MSG_BUFFER_SIZE, "R5:%d",R5);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}


if ((char)message[1] == '6' && (char)message[2] == ':'){
if((char)message[3] == '1'){R6=1;}
else  { R6=0;}
EEPROM.write(106,R6);
  snprintf (msg, MSG_BUFFER_SIZE, "R6:%d",R6);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}


if ((char)message[1] == '7' && (char)message[2] == ':'){
if((char)message[3] == '1'){R7=1;}
else  { R7=0;}
EEPROM.write(107,R7);
  snprintf (msg, MSG_BUFFER_SIZE, "R7:%d",R7);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}


if ((char)message[1] == '8' && (char)message[2] == ':'){
if((char)message[3] == '1'){R8=1;}
else  { R8=0;}
EEPROM.write(108,R8);
  snprintf (msg, MSG_BUFFER_SIZE, "R8:%d",R8);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}


if ((char)message[1] == '9' && (char)message[2] == ':'){
if((char)message[3] == '1'){R9=1;}
else  { R9=0;}
EEPROM.write(101,R9);
  snprintf (msg, MSG_BUFFER_SIZE, "R9:%d",R9);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}


if ((char)message[1] == '1' && (char)message[2] == '0'){
if((char)message[4] == '1'){R10=1;}
else  { R10=0;}
EEPROM.write(110,R10);
  snprintf (msg, MSG_BUFFER_SIZE, "R10:%d",R10);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}


if ((char)message[1] == '1' && (char)message[2] == '1'){
if((char)message[4] == '1'){R11=1;}
else  { R11=0;}
EEPROM.write(111,R11);
  snprintf (msg, MSG_BUFFER_SIZE, "R11:%d",R11);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}

//PWMD0:
if ((char)message[1] == 'W' && (char)message[3] == 'M'&& (char)message[4] == 'D'){
PWMD0 = ((int)message[5]-48)*100+((int)message[6]-48)*10+((int)message[7]-48);
  if (PWMD0<0 ){PWMD0=0;}
 if (PWMD0>240){PWMD0=255;}

EEPROM.write(112,PWMD0);
  snprintf (msg, MSG_BUFFER_SIZE, "PWMD0:%d",PWMD0);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}

if ((char)message[1] == 'W' && (char)message[3] == '1'&& (char)message[4] == ':'){
PWMD1 = ((int)message[5]-48)*100+((int)message[6]-48)*10+((int)message[7]-48);
  if (PWMD1<0 ){PWMD1=0;}
 if (PWMD1>240){PWMD1=255;}
EEPROM.write(113,PWMD1);
  snprintf (msg, MSG_BUFFER_SIZE, "PWMD1:%d",PWMD1);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}
if ((char)message[1] == 'W' && (char)message[3] == '2'&& (char)message[4] == ':'){
PWMD2 = ((int)message[5]-48)*100+((int)message[6]-48)*10+((int)message[7]-48);
  if (PWMD2<0 ){PWMD2=0;}
 if (PWMD2>240){PWMD2=255;}
EEPROM.write(114,PWMD2);
  snprintf (msg, MSG_BUFFER_SIZE, "PWMD2:%d",PWMD2);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}
if ((char)message[1] == 'W' && (char)message[3] == '3'&& (char)message[4] == ':'){
PWMA0 = ((int)message[5]-48)*100+((int)message[6]-48)*10+((int)message[7]-48);
  if (PWMA0<0 ){PWMA0=0;}
 if (PWMA0>240){PWMA0=255;}
EEPROM.write(115,PWMA0);
  snprintf (msg, MSG_BUFFER_SIZE, "PWMA0:%d",PWMA0);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}
if ((char)message[1] == 'W' && (char)message[3] == '4'&& (char)message[4] == ':'){
PWMA1 = ((int)message[5]-48)*100+((int)message[6]-48)*10+((int)message[7]-48);
  if (PWMA1<0 ){PWMA1=0;}
 if (PWMA1>240){PWMA1=255;}
EEPROM.write(116,PWMA1);
  snprintf (msg, MSG_BUFFER_SIZE, "PWMA1:%d",PWMA1);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}
if ((char)message[1] == 'W' && (char)message[3] == '5'&& (char)message[4] == ':'){
PWMA2 = ((int)message[5]-48)*100+((int)message[6]-48)*10+((int)message[7]-48);
  if (PWMA2<0 ){PWMA2=0;}
 if (PWMA2>240){PWMA2=255;}
EEPROM.write(117,PWMA2);
  snprintf (msg, MSG_BUFFER_SIZE, "PWMA2:%d",PWMA2);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
}

 if ((char)message[0] == 'L'&&(char)message[1] == 'M'){
if ((char)message[3] == '0'){ LM=0;}
if ((char)message[3] == '1'){ LM=1;}
 EEPROM.write(118,LM);
 }
 if ((char)message[0] == 'T'&&(char)message[1] == ':'){
T = ((int)message[2]-48)*100+((int)message[3]-48)*10+((int)message[4]-48);
  snprintf (msg, MSG_BUFFER_SIZE, "T:%d",T);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
 }

  if ((char)message[0] == 'L'&&(char)message[1] == 'D' &&(char)message[2] == 'R'){
LDR = ((int)message[4]-48)*1000+((int)message[5]-48)*100+((int)message[6]-48)*10+((int)message[7]-48);
  snprintf (msg, MSG_BUFFER_SIZE, "T:%d",LDR);
   client.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
 }
    client.publish(Pub,(const uint8_t*)message, MSG_BUFFER_SIZE ,true);
  //snprintf (msg, MSG_BUFFER_SIZE, "R0:%d R1:%d R2:%d R3:%d R4:%d R5:%d R6:%d R7:%d R8:%d R9:%d R10:%d R11:%d PWMD0:%03d PWMD1:%03d PWMD2:%03d PWMA0:%03d PWMA1:%03d PWMA2:%03d T:%03d D:%04d LM:%d",R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,PWMD0,PWMD1,PWMD2,PWMA0,PWMA1,PWMA2,T,LD,LM);
  //lient.publish(Pub,(const uint8_t*)msg, MSG_BUFFER_SIZE ,true);
     message_pos = 0;
   }
 }
yield(); 

server.handleClient();
if(!client.connected()){connectMqTT();
digitalWrite(mqtterror,HIGH);}
else{digitalWrite(mqtterror,LOW);
  client.loop();}
 if (chk !=digitalRead(HS)){ ESP.restart();}
 if (chk == false &&digitalRead(HS)==0 ){server.handleClient();}
 if (WiFi.status() == WL_CONNECTED) {digitalWrite(wifierror,LOW);}

else{digitalWrite(wifierror,HIGH);}
if(chk == false){
  // MDNS.update();
  digitalWrite(htspt,HIGH);
 //Serial.print("27s");
 }
  else { digitalWrite(htspt,LOW);
  }
    MDNS.update();
}
