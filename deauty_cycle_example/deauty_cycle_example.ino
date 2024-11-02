int DutyCycle ;
int x ;
void setup() {
pinMode(3,OUTPUT);
DutyCycle = 25 ;
}

void loop() {
 x = DutyCycle *255 /100 ;
analogWrite(3,x);
}


// For UNO 490 Hz (pins 5 and 6: 980 Hz)
