

/**
 * @file Encoder.cpp
 * @brief This file contains the implementation for handling rotary encoder inputs.
 *
 * A rotary encoder is used to convert the angular position or motion of a shaft to 
 * an analog or digital signal. This implementation is specifically designed to work 
 * with a rotary encoder that produces two phase signals (A and B) to determine 
 * the direction of rotation as well as an additional signal (Z) for indexing or 
 * reset purposes. The encoder's counts, pulse durations, and rotation direction 
 * are calculated and can be accessed via functions.
 *
 * Key Features:
 * - Tracks the counts of the encoder phases (A and B)
 * - Measures pulse ticks between changes to calculate speed
 * - Determines the direction of rotation
 * - Resets counters and tick measurements on index signal (Z)
 * - Handles timer overflows using Timer2 to manage pulse timing
 *
 * Variables:
 * - EncoderPhaseACounter: Counts the number of phase A transitions
 * - EncoderPhaseBCounter: Counts the number of phase B transitions
 * - pulseTicksA, pulseTicksB, pulseTicksZ: Duration of pulses between transitions
 * - TimerOverflowCount: Counts timer overflows to handle longer durations
 * - lastTicksA, lastTicksB, lastTicksZ: Ticks from the last transition for pulse timing
 * - EncoderRotationDirection: Holds the current direction of rotation (CLOCKWISE or COUNTERCLOCKWISE)
 *
 * This implementation requires proper pin configurations and should be integrated 
 * with a suitable interrupt handling mechanism to ensure accurate readings.
 */

#include "Encoder.h"
volatile int EncoderPhaseACounter = 0; // Counter for phase A transitions
volatile int EncoderPhaseBCounter = 0; // Counter for phase B transitions
volatile uint32_t pulseTicksA = 0;          // Duration of pulses for phase A
volatile uint32_t pulseTicksB = 0;          // Duration of pulses for phase B
volatile uint32_t pulseTicksZ = 0;          // Duration of pulses for index signal (Z)

volatile uint8_t TimerOverflowCount = 0;    // To handle overflow for timing accuracy
volatile uint32_t lastTicksA = 0;            // Last recorded ticks for phase A
volatile uint32_t lastTicksB = 0;            // Last recorded ticks for phase B
volatile uint32_t lastTicksZ = 0;            // Last recorded ticks for index signal (Z)
uint8_t EncoderRotationDirection;             // Direction of rotation (CLOCKWISE or COUNTERCLOCKWISE)

void EncoderInit() {
  // Set encoder pins as input with pull-up resistors
  pinMode(ENCODER_PINA, INPUT_PULLUP);
  pinMode(ENCODER_PINB, INPUT_PULLUP);
  pinMode(ENCODER_PINZ, INPUT_PULLUP);

  // Attach pin change interrupts for the encoder phases
  attachPCINT(digitalPinToPCINT(ENCODER_PINA), EncoderPhaseA, FALLING);
  attachPCINT(digitalPinToPCINT(ENCODER_PINB), EncoderPhaseB, FALLING);
  attachPCINT(digitalPinToPCINT(ENCODER_PINZ), EncoderPhaseZ, FALLING);

  // Set up Timer2 for pulse measurement
  TCCR2A = 0;                 // Configure Timer2 in normal mode
  TCCR2B = (1 << CS21);      // Set prescaler to 8 for Timer2
  TCNT2 = 0;                  // Start with Timer2 count of 0
  TIMSK2 = (1 << TOIE2);     // Enable Timer2 overflow interrupt
}

void EncoderPhaseA() {
  uint32_t currentTicks = (TimerOverflowCount << 8) + TCNT2;  // Calculate ticks with overflow handling
  pulseTicksA = currentTicks - lastTicksA;  // Calculate duration of pulse A
  lastTicksA = currentTicks;                  // Update last ticks for A
  // Determine the rotation direction based on phase B state
  EncoderRotationDirection = (digitalRead(ENCODER_PINB)) ? COUNTERCLOCKWISE : CLOCKWISE;

  if(EncoderRotationDirection == CLOCKWISE){
  EncoderPhaseACounter++;                     // Increment phase A counter
  } else{
  EncoderPhaseACounter--;                     // Decrement phase A counter
  }
  
}

void EncoderPhaseB() {
  uint32_t currentTicks = (TimerOverflowCount << 8) + TCNT2;  // Calculate ticks with overflow handling
  pulseTicksB = currentTicks - lastTicksB;  // Calculate duration of pulse B
  lastTicksB = currentTicks;                  // Update last ticks for B

  // Determine the rotation direction based on phase B state
  EncoderRotationDirection = (digitalRead(ENCODER_PINA)) ? CLOCKWISE : COUNTERCLOCKWISE;


    if(EncoderRotationDirection == CLOCKWISE){
  EncoderPhaseBCounter++;                     // Increment phase B counter
  } else{
  EncoderPhaseBCounter--;                     // Decrement phase B counter
  }

}

void EncoderPhaseZ() {
  
  uint32_t currentTicks = (TimerOverflowCount << 8) + TCNT2;  // Calculate ticks with overflow handling
  pulseTicksZ = currentTicks - lastTicksZ;  // Calculate duration of pulse Z
  lastTicksZ = currentTicks;                  // Update last ticks for Z
  
  // Reset counters and overflow count on Z signal
  EncoderPhaseACounter = 0; 
  EncoderPhaseBCounter = 0; 
  TimerOverflowCount = 0;  // Reset overflow count
  TCNT2 = 0;               // Reset Timer2 count
}

float EncoderGetRPM() {
  // Calculate RPM based on pulseTicksZ duration
  return 1000000 / (TICKS_TO_US(pulseTicksZ)); // Frequency = 1 / Period (in microseconds)
}

float EncoderGetAngle() {
  // Calculate the angle based on phase A and B counts
  return (((float)(abs(EncoderPhaseACounter)) * (360.0 / ENCODER_PPR)) + 
          ((float)(abs(EncoderPhaseBCounter)) * (360.0 / ENCODER_PPR))) / 2.0;
}

bool EncoderGetDirection() {
  // Return the current direction of rotation
  return EncoderRotationDirection;
}

// Timer2 overflow interrupt service routine
ISR(TicksR2_OVF_vect) {
  TimerOverflowCount++;  // Increment overflow count on each overflow
}
