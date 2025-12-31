#pragma once
/*
  Module: ecg_signal
  Purpose: ECG analog sampling, buffer maintenance, and buzzer gating
  Author:  Abdelrahman Elnahrawy
  License: MIT

  API:
    - ecg_buffer_init(buffer, width, baseline)
    - ecg_update_from_analog(buffer, width, analog_pin, analog_max, ecg_height, buzzer_pin)
      returns normalized percent [0..100]
*/

#include <Arduino.h>

void ecg_buffer_init(int *buffer, uint8_t width, int baseline);
int  ecg_update_from_analog(int *buffer, uint8_t width, uint8_t analog_pin,
                            int analog_max, uint8_t ecg_height, uint8_t buzzer_pin);
