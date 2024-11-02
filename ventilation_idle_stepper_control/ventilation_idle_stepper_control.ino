

#include <Stepper.h>

const int stepsPerRevolution = 200;// change this to fit the number of steps per revolution
float AIR ;
float OIR ; 
//AIR = Air    Idle valve opening Ratio
//OIR = Oxygen Idle valve opening Ratio
float OFS ;
// OFS = oxygen flowrate sensor readings
float OF ;
//OF =oxygen flowrate required
float AF ;
//AF =air flowrate required
float AFS ;
// AFS = air flowrate sensor readings

Stepper IACO(stepsPerRevolution, 8, 9, 10, 11);
Stepper IACA(stepsPerRevolution, 4, 5, 6, 7);
void setup() {
  IACO.setSpeed(60);
  IACA.setSpeed(60);
  Serial.begin(9600);
}

void loop() {
  AIR = (100-oxygen)/79;
  OIR  = 1-AIR;
  OF = OIR*volume ;
  AF = AIR*volume ;
  if (AFS<AF){IACA.step(stepsPerRevolution); }
  if (AFS>AF){IACA.step(-stepsPerRevolution);}
  if (OFS<OF){IACO.step(stepsPerRevolution); }
  if (OFS>OF){IACO.step(-stepsPerRevolution);}

}
