#ifndef ECGDISPLAY_H
#define ECGDISPLAY_H

#include "OLEDDisplay.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define HEADER_HEIGHT 10
#define ECG_HEIGHT (SCREEN_HEIGHT - HEADER_HEIGHT)

void initECG();
void updateECGBuffer();
void drawECG();

#endif