#include "GUI_Handler.h"
#include "Stepper_Handler.h"
#include "Encoder.h"
#include "FreqGenPin11.h"
// Control modes
#define SCREEN_SELECTION 0
#define SCREEN_SPEED     1
#define SCREEN_ANGLE     2
uint8_t CurrentMode;
uint32_t UpdateMillis;

#define CORRECTION_PERIOD_FOR_SPEED_CONTROL   500 //in ms
#define CORRECTION_PERIOD_FOR_ANGLE_CONTROL   500 //in ms

void setup() {
  
  Serial.begin(115200);
  DisplaySetup();
  StepperSetup(13,12);
  StepperSetSpeed(100);
  StepperDisable  (); 
  delay(100);
  EncoderInit();
  delay(100);
}

void loop() {
delay(1000);
Serial.print("Current Angle = ");
Serial.print(EncoderGetAngle());
}
