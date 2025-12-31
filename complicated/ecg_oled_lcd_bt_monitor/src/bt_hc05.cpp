#include "bt_hc05.h"

void bt_begin(SoftwareSerial &bt) {
  bt.begin(9600);
  delay(100);
  bt.println("ECG+SpO2 Monitor Ready");
}

void bt_publish(SoftwareSerial &bt, int ecg_percent, int spo2, int bpm) {
  bt.print("ECG:"); bt.print(ecg_percent);
  bt.print("%,SpO2:"); bt.print(spo2);
  bt.print("%,BPM:"); bt.println(bpm);
}
