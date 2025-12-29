#ifndef OLEDDISPLAY_H
#define OLEDDISPLAY_H

#include <U8g2lib.h>
#include <Wire.h>

extern U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2;

void initOLED();
void clearOLED();

#endif