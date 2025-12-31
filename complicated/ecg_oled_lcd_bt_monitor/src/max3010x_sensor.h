#pragma once
/*
  Module: max3010x_sensor
  Purpose: Minimal MAX30102/30105 sampling and naive BPM/SpO2 estimation
  Author:  Abdelrahman Elnahrawy
  License: MIT

  API:
    - max3010x_begin(max)
    - max3010x_update_and_compute(max)
    - max3010x_get_bpm()
    - max3010x_get_spo2()

  Notes:
    - Uses SparkFun MAX30105 library to access MAX30102.
    - Simple estimation approach, not medically accurate.
*/

#include <Arduino.h>
#include <MAX30105.h>

void max3010x_begin(MAX30105 &sensor);
void max3010x_update_and_compute(MAX30105 &sensor);
int  max3010x_get_bpm();
int  max3010x_get_spo2();
