#pragma once
/*
  Module: display_lcd
  Purpose: 16x2 I2C LCD screen routines used by ECG + Pulse/SpO2 monitor
  Author:  Abdelrahman Elnahrawy
  License: MIT

  API:
    - lcd_init_screen(lcd): one-time initialization and static labels
    - lcd_show_values(lcd, bpm, spo2): prints validated numbers or "ERR"

  Notes:
    - Pass a reference to an instantiated LiquidCrystal_I2C object.
    - Keep LCD address configuration and object lifetime in the sketch.
*/

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD and write static labels
void lcd_init_screen(LiquidCrystal_I2C &lcd);

// Render validated values; prints "ERR" if out of the allowed range
void lcd_show_values(LiquidCrystal_I2C &lcd, int bpm, int spo2);
