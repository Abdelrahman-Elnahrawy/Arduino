#include "HC05Bluetooth.h"
#include <SoftwareSerial.h>

// Define SoftwareSerial for HC-05
SoftwareSerial BTSerial(10, 11);  // RX, TX

void initBluetooth() {
  // Initialize SoftwareSerial
  BTSerial.begin(9600);   // HC-05 default baud
  delay(100);

  // Optional: send a welcome message
  BTSerial.println("HMU - MEDITRONICS 1.1 (maryam team)");
  delay(100);
}

void sendData(int ecgPercent, int spo2Percent, int bpm) {
  // Send as CSV string over SoftwareSerial
  BTSerial.print("ECG:");
  BTSerial.print(ecgPercent);
  BTSerial.print("%,SpO2:");
  BTSerial.print(spo2Percent);
  BTSerial.print("%,BPM:");
  BTSerial.println(bpm);
}
