int state = LOW;
void led (){
  state = (state == LOW)?HIGH:LOW;
  digitalWrite(4,state);
  }
void setup() {
pinMode(4,OUTPUT);
pinMode(2,INPUT );
digitalWrite(2, HIGH );
attachInterrupt( digitalPinToInterrupt(2), led , FALLING);
}
void loop() {

}
