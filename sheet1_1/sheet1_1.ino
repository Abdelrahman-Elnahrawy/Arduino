
// pulse for 2 seconds

int x = 2000*25/100;
void setup() {
pinMode(7,OUTPUT);


}

void loop() {
 digitalWrite(7,HIGH);
 delay(500);
 digitalWrite(7,LOW);
 delay(1500);
}
