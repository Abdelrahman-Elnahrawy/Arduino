
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','a'},
  {'4','5','6','b'},
  {'7','8','9','c'},
  {'*','0','#','d'}
};
byte rowPins[ROWS] = {9,8,7,6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5,4,3,2}; //connect to the column pinouts of the keypad
//وصل ال 8 عند بين 9 و انزل بيهم
int mode = 1;
int x = 2;
int S = 0;
float oxygen =21;
int IT = 0 ;
//type of the entered data
float MP = 25 ;
float rate = 15;
float volume = 500 ;
int ratio;
unsigned long previousMillis0 = 0;
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  unsigned long currentMillis0 = millis();
  int key = keypad.getKey()-48;
  if (key == 49){IT= 1;    x =2;    S =0; 
  previousMillis0 = currentMillis0;}
  if (key == 50){IT= 2;    x =2;    S =0;
  previousMillis0 = currentMillis0;}
  if (key == 51){IT= 3;    x =2;    S =0;
  previousMillis0 = currentMillis0;}
  if (key == 52){IT= 4;    x =2;    S =0;
  previousMillis0 = currentMillis0;}
  if (key == 42){mode+= 1;
  if (mode>4){mode = 1;}}
  if (key == 35){ratio+= 1;
  if (ratio>3){ratio = 1;}}
  if (IT ==1){
  if (key>=0 && key<=9){
    S = S+1+key*pow(10,x);
    S = S /10;
    S = S *10;
    x=x-1;
    oxygen = S/10;
    previousMillis0 = currentMillis0;
    Serial.print("the oxygen:");
    Serial.println(oxygen);}
    if (oxygen<21 ){oxygen = 21 ;}
    if (oxygen>100){oxygen = 100;}
    if (currentMillis0 - previousMillis0 >=1500) {
    IT=0;
    x =2;
    S =0;}}
  if (IT ==2){
  if (key>=0 && key<=9){
    S = S+1+key*pow(10,x);
    S = S /10;
    S = S *10;
    x=x-1;
    MP = S/10;
    previousMillis0 = currentMillis0;
    Serial.print("the MP:");
    Serial.println(MP);}
    if (MP<10 ){MP = 10 ;}
    if (MP>37){MP = 37;}
    if (currentMillis0 - previousMillis0 >=1500) {
    IT=0;
    x =2;
    S =0;}}
if (IT ==3){
  if (key>=0 && key<=9){
    S = S+1+key*pow(10,x);
    S = S /10;
    S = S *10;
    x=x-1;
    rate = S/10;
    previousMillis0 = currentMillis0;
    Serial.print("the rate:");
    Serial.println(rate);}
    if (rate<10 ){rate = 10 ;}
    if (rate>30){rate = 30;}
    if (currentMillis0 - previousMillis0 >=1500) {
    IT=0;
    x =2;
    S =0;}}
if (IT ==4){
  if (key>=0 && key<=9){
    S = S+1+key*pow(10,x);
    S = S /10;
    S = S *10;
    x=x-1;
    volume = S;
    previousMillis0 = currentMillis0;
    Serial.print("the volume:");
    Serial.println(volume);}
    if (volume<270){volume = 270 ;}
    if (volume>800){volume = 800; }
    if (currentMillis0 - previousMillis0 >=1500) {
    IT=0;
    x =2;
    S =0;}}
}
