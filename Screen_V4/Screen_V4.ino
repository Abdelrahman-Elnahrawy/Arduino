#include "GUI_Handler.h"
#include "Stepper_Handler.h"
#include "Encoder.h"
#include "FreqGenPin11.h"
// Control modes
#define SCREEN_SELECTION 0
#define SCREEN_SPEED     1
#define SCREEN_ANGLE     2
uint8_t CurrentMode;
void setup() {
  
  Serial.begin(115200);
  DisplaySetup();
  StepperSetup(13,12);
  StepperSetSpeed(100);
  StepperDisable  (); 
  delay(100);
}

void loop() {
  /*
  FreqGenGeneratePulses(100,100);
  delay(2000);
  */

  char buttonState = readLCDButtons(); // Read button state
  if (buttonState != BUTTON_NULL) {
    DisplayUpdate(buttonState );
    CurrentMode = GUIGetMode();
    bool RotationDirection = GUIGetDirection();
    StepperSetDirection(RotationDirection);
    switch (CurrentMode){
      case MODE_SELECT:
      StepperDisable  ();    
      break;
      case SPEED_CONTROL:
      Serial.println("speed Control Update");
      StepperEnable  ();
      StepperSetSpeed(GUIGetSpeed ());
      break;
      case ANGLE_CONTROL:
      StepperEnable  ();
      if(RotationDirection == CLOCKWISE)
      {
        if(EncoderGetAngle()<GUIGetAngle ())
        {
        StepperSetAngle(GUIGetAngle ());
        }
      }
      else {
        if(EncoderGetAngle()>GUIGetAngle ())
        {
        StepperSetAngle(GUIGetAngle ());
        }
      }
      
      break;
      default:
      break;
    }
  }
  if(CurrentMode == ANGLE_CONTROL){

  }
  
}