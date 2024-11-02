#include "PinChangeInterrupt.h"

#define ENCODER_PINA  8   // PCINT0
#define ENCODER_PINB  9   // PCINT1
#define ENCODER_PINZ  10  // PCINT2
#define ENCODER_PPR   300 // Pulses per revolution for the encoder

#ifndef COUNTERCLOCKWISE 
#define COUNTERCLOCKWISE 1
#endif

#ifndef CLOCKWISE 
#define CLOCKWISE 0
#endif

volatile uint16_t EncoderPhaseACounter = 0;
volatile uint16_t EncoderPhaseBCounter = 0;
volatile uint32_t pulseTicksA = 0;
volatile uint32_t pulseTicksB = 0;
volatile uint32_t pulseTicksZ = 0;

volatile uint8_t TimerOverflowCount = 0;  // To handle overflow

volatile uint32_t lastTicksA = 0;
volatile uint32_t lastTicksB = 0;
volatile uint32_t lastTicksZ = 0;

#define TICKS_TO_MS(ticks) ((ticks) / 2000.0)
#define TICKS_TO_US(ticks) ((ticks) / 2)

void EncoderInit() {
  // Set pin to input with a pullup
  pinMode(ENCODER_PINA, INPUT_PULLUP);
  pinMode(ENCODER_PINB, INPUT_PULLUP);
  pinMode(ENCODER_PINZ, INPUT_PULLUP);

  // Attach pin change interrupts for encoder
  attachPCINT(digitalPinToPCINT(ENCODER_PINA), EncoderPhaseA, RISING);
  attachPCINT(digitalPinToPCINT(ENCODER_PINB), EncoderPhaseB, RISING);
  attachPCINT(digitalPinToPCINT(ENCODER_PINZ), EncoderPhaseZ, RISING);

  // Set up Ticksr 2
  TCCR2A = 0;                 // Normal mode
  TCCR2B = (1 << CS21);  // Set prescaler to 8
  TCNT2 = 0;                   // Start with Ticksr count of 0
  TIMSK2 = (1 << TOIE2);       // Enable Ticksr 2 overflow interrupt
}

void EncoderPhaseA() {
  uint32_t currentTicks = (TimerOverflowCount << 8) + TCNT2;  // Calculate Ticks with overflow handling
  pulseTicksA = currentTicks - lastTicksA;  // Ticks between pulses
  lastTicksA = currentTicks;
  EncoderPhaseACounter++;
}

void EncoderPhaseB() {
  uint32_t currentTicks = (TimerOverflowCount << 8) + TCNT2;  // Calculate Ticks with overflow handling
  pulseTicksB = currentTicks - lastTicksB;  // Ticks between pulses
  lastTicksB = currentTicks;
  EncoderPhaseBCounter++;
}

void EncoderPhaseZ() {
  uint32_t currentTicks = (TimerOverflowCount << 8) + TCNT2;  // Calculate Ticks with overflow handling
  pulseTicksZ = currentTicks - lastTicksZ;  // Ticks between pulses
  lastTicksZ = currentTicks;
  EncoderPhaseACounter = 0; 
  EncoderPhaseBCounter = 0; 
  TimerOverflowCount = 0;  // Reset overflow count
  TCNT2 = 0;               // Reset Ticksr 2
}

float EncoderGetRPM(){
return 1000000/(TICKS_TO_US(pulseTicksZ)); //requency = 1/ periodic time , the 1 million above is as the ticks in microseconds
}

float EncoderGetAngle(){
  return (((float)(EncoderPhaseACounter)*(360/ENCODER_PPR))+((float)(EncoderPhaseBCounter)*(360/ENCODER_PPR)))/2 ;
}

ISR(TicksR2_OVF_vect) {
  TimerOverflowCount++;  // Increment overflow count on each overflow
}

bool EncoderGetDirection(){
return (EncoderPhaseACounter>EncoderPhaseBCounter)? CLOCKWISE : COUNTERCLOCKWISE ;
}
void setup() {
  Serial.begin(115200);
  EncoderInit();
}


void loop() {
  // Print pulse Tickss for debugging (optional)
  Serial.print("Pulse Ticks A: ");
  Serial.println(pulseTicksA);
  Serial.print("Pulse Ticks B: ");
  Serial.println(pulseTicksB);

  delay(1000);  // Delay for readability
}
