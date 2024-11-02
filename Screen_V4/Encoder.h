#ifndef ENCODER_HANDLER_H
#define ENCODER_HANDLER_H


#include "PinChangeInterrupt.h"

#define ENCODER_PINA  2   // PCINT0
#define ENCODER_PINB  3   // PCINT1
#define ENCODER_PINZ  10  // PCINT2
#define ENCODER_PPR   300 // Pulses per revolution for the encoder

#ifndef COUNTERCLOCKWISE 
#define COUNTERCLOCKWISE 1
#endif

#ifndef CLOCKWISE 
#define CLOCKWISE 0
#endif

#define TICKS_TO_MS(ticks) ((ticks) / 2000.0)
#define TICKS_TO_US(ticks) ((ticks) / 2)


void EncoderInit();
void EncoderPhaseA();
void EncoderPhaseB();
void EncoderPhaseZ();
float EncoderGetRPM();
float EncoderGetAngle();
bool EncoderGetDirection();

#endif