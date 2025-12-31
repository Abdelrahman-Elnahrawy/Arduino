#pragma once
/*
  Module: display_lcd
  Purpose: 16x2 I2C LCD screen routines for Pulse/SpO2 demo
  Author:  Abdelrahman Elnahrawy
  License: MIT

  API:
    - lcd_init_screen(lcd): one-time initialization and static labels
    - lcd_show_values(lcd, bpm, spo2): prints validated numbers or "ERR"
*/

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

void lcd_init_screen(LiquidCrystal_I2C &lcd);
void lcd_show_values(LiquidCrystal_I2C &lcd, int bpm, int spo2);
