

int LEDS[4] = {4,5,6,7} ;
void setup() {
for (int i=0;i<4;i++){
  pinMode(LEDS[i],OUTPUT);
}

}

void loop() {
for(int i=0;i<4;i++){
  digitalWrite(LEDS[i],HIGH);
  delay(500);
  digitalWrite(LEDS[i],LOW);
 }
 digitalWrite(7,HIGH);
 for(int i=3;i>0;i--){
digitalWrite(LEDS[i],HIGH);
  delay(500);
  digitalWrite(LEDS[i],LOW);
  }
}
