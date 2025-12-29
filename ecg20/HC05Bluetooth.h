#ifndef HC05BLUETOOTH_H
#define HC05BLUETOOTH_H

#include <Arduino.h>

// Initialize HC-05 (hardware Serial on pins 0/1)
void initBluetooth();  

// Send ECG %, SpO2 %, and BPM via Bluetooth
void sendData(int ecgPercent, int spo2Percent, int bpm);

#endif