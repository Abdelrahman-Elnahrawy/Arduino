/**************************************************************
 *Introduction to Embeded systems *****ASU COURSE**************
 * 888888888888888888888---SHEET_2---88888888888888888888888888
 * TO COMBILE THE CODE OR PLAY WITH IT UN COMMENT THE SECTION**
 * NEEDED ************THANK U <3 <<<<>>>>>><<<<<<>>>>>><<<<>>>>
 *************************************************************/


 


 /*************************************************************
 * 888888888888888888888---SHEET_2-1-88888888888888888888888888
 **********************PWM_VIA_DIP_8bit***********************/





/*************************************************************
 for proteus simulation u need to connect pull down resistor network 
 on the dips pins to work correctly
*************************************************************/


/*************************************************************
#define LED  13 
int   DIP[] = {2,3,4,5,6,7,8,9} ;
float value   =0;
float oldvalue=0;

void setup() {
    Serial.begin(9600);
  for(int i=0; i<8 ; i++){
 Serial.print("i as output :  ");
 delay(50);         // to fix proteus stuck
 Serial.println(i+2);
 digitalWrite(DIP[i],LOW);
 pinMode(DIP[i],INPUT);
  }
  pinMode(LED,OUTPUT);
}

void loop() {
  value = 0;
for(int x=0; x<8 ;x++){
  value = value + ((digitalRead(2+x)*pow(2,x)));
}

if (value != oldvalue){
  analogWrite(13,value);
 oldvalue = value  ;}
}
*************************************************************/


 /*************************************************************
 * 888888888888888888888---SHEET_2-2-88888888888888888888888888
 ****************blink_using_interrupts _and_timers***********/




  /*************************************************************
 * 888888888888888888888with_intrrupts88888888888888888888888888
 ****************blink_using_interrupts _and_timers***********/


  /*************************************************************
#define LED 13
#define DOWN 2
#define UP   3

int x = 0 ;
void decrease(){
  x-- ;
      if (x<0){
      x=0;
      }
      Serial.print("the x value is :  ");
      Serial.println(x);
  }
  void increase(){
    x++;
    if (x>10){
      x=10;
      }
      Serial.print("the x value is :  ");
      Serial.println(x);
      
  }
 void setup(){
  pinMode(13 ,OUTPUT);
  pinMode(UP  ,INPUT);
  pinMode(DOWN,INPUT);
  attachInterrupt(digitalPinToInterrupt(UP   ), increase, RISING) ;
  attachInterrupt(digitalPinToInterrupt(DOWN),  decrease, RISING) ;
  Serial.begin(9600); 
 }
 void loop () {

  digitalWrite (LED,HIGH);
  delay (x*500);
  digitalWrite (LED,LOW) ;
  delay (x*500);
 }

 ****************blink_using_interrupts _and_timers***********/


  /*************************************************************
 * 88888888888888888888without_intrrupts888888888888888888888888
 ****************blink_using_interrupts _and_timers***********/
 
/***********************blinktime_control**********************
 
#define LED 13
#define DOWN 2
#define UP   3
boolean state ;
int x = 1 ;
unsigned long long timer = 0;
void setup(){
  pinMode(LED,OUTPUT);
  pinMode(DOWN,INPUT);
  pinMode(UP  ,INPUT);
  digitalWrite(UP  ,LOW);
  digitalWrite(DOWN,LOW);
}
void loop(){
  if (digitalRead(UP)){
    delay(50);
      if (digitalRead(UP)){
        x++;
        while(1){
          if (!digitalRead(UP)){
            break;}
          }
        }
    if(x>10){x =10 ;}
  }

    if (digitalRead(DOWN)){
    delay(50);
      if (digitalRead(DOWN)){
        x--;
        while(1){
          if (!digitalRead(DOWN)){
            break;}
          }
        }
    if(x<1){x =1 ;}
  }
  
 if(millis()- timer >500*x){
 digitalWrite(LED,HIGH);
 }
 if(millis()- timer >1000*x){
digitalWrite(LED, LOW);
timer = millis();
}
}

************************blinktime_control**********************/


 /*************************************************************
 * 888888888888888888888---SHEET_2-3-88888888888888888888888888
 **********************binary_counter*************************/


 
 /**********************binary_counter*************************
int LEDS[]={2,3,4,5,6,7,8,9,10} ;
unsigned int number ;
 void setup(){
  for(int i ; i>9 ; i++){
    pinMode(LEDS[i],OUTPUT);
    }
 }
 void loop(){
  number++ ;
    if(number>255){number = 0;}
for(int i ; i>9 ; i++){
  digitalWrite(LEDS[i],number & 1<<i);
 
 }
  delay(1000);
 }
 **********************binary_counter*************************/
 /***********************************************************************************************************************************
    digitalWrite(2,number & 1<<2);   ??/// means   for examble 3 in binary 0000 0011 & 1<<2 = 0000 0011 & 0000 0010 = 0000 0010  which 
    is two and as the digital write take positve values so it will turn on but if the number doesnt contain the specified digit in the
    binary the and will return with zero value so the boolean (high or low ) is set to zero example 0001 1000 & 0000 0010 = 0000 0000 
    so it set the led off
  ***********************************************************************************************************************************/

 /*************************************************************
 * 888888888888888888888---SHEET_2-4-88888888888888888888888888
 ************************analog_play**************************/

 
/*************************analog_play**************************
 #define LED 13
 int x;
void switch_button(){
  x++;
  if(x>5){
    x=0;
  }
 Serial.print("the cycle time in ms became :  ");
  Serial.println(analogRead(x));
}
 void setup(){
  pinMode(LED,OUTPUT);
  analogReference(DEFAULT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2),switch_button,RISING);
 }
 void loop (){
  
  interrupts();
digitalWrite(LED,HIGH);
delay(analogRead(x)/2);
digitalWrite(LED,LOW);
delay(analogRead(x)/2);
 }
************************analog_play**************************/



 /*************************************************************
 * 888888888888888888888---SHEET_2-5-88888888888888888888888888
 ***************************analog_read***********************/

 /***************************analog_read***********************

 int LEDS[10] {2,3,4,5,6,7,8,9,10,11,12} ;
 void setup(){
  analogReference(DEFAULT);
  for(int i; i>10; i++){
  pinMode(LEDS[i],OUTPUT);
 }
 void loop (){
   for(int i; i>10; i++){
  digitalWrite(LEDS[i],HIGH);
  delay(analogRead(0));
  digitalWrite(LEDS[i],LOW );
 }
 }
  ***************************analog_read***********************/




 /*************************************************************
 * 888888888888888888888---SHEET_2-6-88888888888888888888888888
 ************************do_it_yourself***********************/



 

 /*************************************************************
 * 888888888888888888888---SHEET_2-7-88888888888888888888888888
 **************************LOMAD_EL_FARA7*********************/

/**************************LOMAD_EL_FARA7**********************
const int buttonPin = 2;    
const int ledPin = 13;      
int ledstate = HIGH;                      
boolean BLINK = false ;  
unsigned long blinktime = 0;  
unsigned long presstime = 0;  
void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledstate);
  digitalWrite(buttonPin, HIGH);  
}
void loop() {
if (digitalRead(buttonPin)==LOW){
  presstime = millis () ;
  while(1){
    if (digitalRead(buttonPin)== HIGH){break ;}
    }
if (millis() - presstime>80){  ////// THIS IF IS TO CHEK THE REBOUNCE EFFECT
  ledstate = ! ledstate ;
  digitalWrite(ledPin, ledstate);}
if (millis() - presstime>5000){ 
  BLINK  = !BLINK;}

}

 if (BLINK){
 if (millis() - blinktime > 400 ){ledstate = ! ledstate ;
    digitalWrite(ledPin, ledstate);
    blinktime = millis();
 }
}
}
**************************LOMAD_EL_FARA7*********************/



/*########################################################################################################################################################################################
thank u <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <33 <3 <3 <3 <3 <3 <3 <3 <3 <3
/########################################################################################################################################################################################*/
