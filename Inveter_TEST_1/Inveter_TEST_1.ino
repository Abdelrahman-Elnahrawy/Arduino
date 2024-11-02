#include <ACS712.h>

#include <MsTimer2.h>
#define FREQUENCY 50000 
#define PERIOD_TIME 1000000/FREQUENCY  // IN MICROSECONDS
#define HIGH_MOSFET_PIN 5
#define  LOW_MOSFET_PIN 6
#define VALUE_UPDATE_TIME 1000 // The value is in ms
#define DUTYCYCLE_INPUT_PIN   A0
#define DEADTIME   1 // in Micro-Seconds
#define DUTY 0.5
     float sensorValue ,OnTime , OffTime ;
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  pinMode(HIGH_MOSFET_PIN, OUTPUT);
  pinMode(LOW_MOSFET_PIN, OUTPUT);
    Dutycycle_Update();
  MsTimer2::set(VALUE_UPDATE_TIME, Dutycycle_Update); // 500ms period
  MsTimer2::start();

}

void loop() {

  digitalWrite(HIGH_MOSFET_PIN, HIGH); 
  // HIGH LOW
   //1    0 
  delayMicroseconds(DEADTIME);
  digitalWrite(LOW_MOSFET_PIN, HIGH);  
  // HIGH LOW
  // 1    1
delayMicroseconds(OnTime);            
  digitalWrite(HIGH_MOSFET_PIN, LOW);
  // HIGH LOW
   // 0   1
  delayMicroseconds(DEADTIME);  
  digitalWrite(LOW_MOSFET_PIN, LOW);  
  // HIGH LOW
   // 0   0
delayMicroseconds(OffTime);                 
}

void Dutycycle_Update()
{

    sensorValue = 1023*DUTY;
    if(sensorValue<=0){
      sensorValue=1;
    }

    OnTime = PERIOD_TIME * (sensorValue/1023) - DEADTIME;
    OffTime = PERIOD_TIME - OnTime - DEADTIME;
    Serial.print("sensorValue:");
    Serial.println(sensorValue);
    Serial.print("ON TIME:");
    Serial.println(OnTime);
    Serial.print("OFF_TIME:");
    Serial.println(OffTime);
}
