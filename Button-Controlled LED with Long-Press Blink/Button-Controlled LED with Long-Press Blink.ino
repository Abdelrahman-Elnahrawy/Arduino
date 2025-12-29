
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
if (millis() - presstime>80){  
  ledstate = ! ledstate ;
  digitalWrite(ledPin, ledstate);}
if (millis() - presstime>3000){ 
  BLINK  = !BLINK;}

}

 if (BLINK){
 if (millis() - blinktime > 400 ){ledstate = ! ledstate ;
    digitalWrite(ledPin, ledstate);
    blinktime = millis();
 }
}
}
