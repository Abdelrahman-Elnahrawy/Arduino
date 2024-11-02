float rate=1;
float ratio=1;
float inhale_time;
float exhale_time;
unsigned long previousMillis =0;
unsigned long time;
void setup() {
inhale_time = (rate/60)/ratio;
exhale_time = (rate/60) - inhale_time;
} 
void loop() {
 time = millis();
  for (previousMillis =millis(); inhale_time+previousMillis<time;time = millis()) {
   //inhale 
   }
for (unsigned long previousMillis =millis(); exhale_time+previousMillis<time;time = millis()) {
  //exhale
  }
}
