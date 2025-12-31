#pragma once
/*
  Module: bt_hc05
  Purpose: HC-05 SoftwareSerial initialization and CSV publishing
  Author:  Abdelrahman Elnahrawy
  License: MIT

  API:
    - bt_begin(bt)
    - bt_publish(bt, ecg_percent, spo2, bpm)

  Notes:
    - Construct SoftwareSerial in the sketch with desired pins and pass by reference.
*/

#include <Arduino.h>
#include <SoftwareSerial.h>

void bt_begin(SoftwareSerial &bt);
void bt_publish(SoftwareSerial &bt, int ecg_percent, int spo2, int bpm);
