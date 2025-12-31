#pragma once
/*
  Module: display_oled
  Purpose: SH1106 128x64 OLED drawing via U8g2
  Author:  Abdelrahman Elnahrawy
  License: MIT

  API:
    - oled_welcome(u8g2): splash page at startup
    - ecg_draw_oled(u8g2, buffer, width, header_h, ecg_h): draw ECG waveform
*/

#include <Arduino.h>
#include <U8g2lib.h>

void oled_welcome(U8G2 &u8g2);
void ecg_draw_oled(U8G2 &u8g2, const int *buffer, uint8_t width, uint8_t header_h, uint8_t ecg_h);
