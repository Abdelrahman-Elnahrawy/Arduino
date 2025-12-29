// mariamoled.ino
#include "OLEDDisplay.h"
#include "ECGDisplay.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Display.h"
#include "HC05Bluetooth.h"
#include "MAX30102.h"

// LCD (adjust address if needed)
LiquidCrystal_I2C lcd(0x20, 16, 2);

// MAX30102 object (lightweight driver)
MAX30102 maxSensor;

// Timing (non-blocking)
const unsigned long MAX_UPDATE_INTERVAL = 200;    // 200 ms => ~5 Hz
const unsigned long DISPLAY_UPDATE_INTERVAL = 1000; // update LCD every 1s
const unsigned long BT_SEND_INTERVAL = 1000;       // send via BT every 1s
const unsigned long ECG_UPDATE_INTERVAL = 100;      // update ECG buffer every 100us

unsigned long lastMaxUpdate = 0;
unsigned long lastDisplayUpdate = 0;
unsigned long lastBTSend = 0;
unsigned long lastECGUpdate = 0;

// Values to display / send
int pulseRate = 0;
int spo2 = 0;

void setup() {
  // Initialize modules
  initBluetooth();        // HC-05 on hardware Serial (pins 0/1)
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  displayInit(lcd);       // your LCD init function (Display.h)
  
  initOLED();             // show welcome screen on OLED (OLEDDisplay)
  initECG();              // prepare ECG buffer (ECGDisplay)

  // Initialize MAX30102 sensor (lightweight)
  maxSensor.begin();

  // Initialize values
  pulseRate = 0;
  spo2 = 0;

  // Small startup delay to let things settle (non-blocking elsewhere)
  delay(50);
}

void loop() {
  unsigned long now = millis();
  unsigned long nowMacros = micros();

  // ---------------------
  // ECG: update buffer at ECG_UPDATE_INTERVAL (fast enough for smooth drawing)
  // ---------------------
  if (now - lastECGUpdate >= ECG_UPDATE_INTERVAL) {
    lastECGUpdate = now;
    updateECGBuffer();    // reads A0, shifts buffer (from ECGDisplay)
    // We draw the ECG immediately after updating to keep display responsive
    drawECG();            // draws header + waveform on OLED
  }

  // ---------------------
  // MAX30102: update at low frequency (~5 Hz)
  // ---------------------
  if (nowMacros - lastMaxUpdate >= MAX_UPDATE_INTERVAL) {
    lastMaxUpdate = nowMacros;
    maxSensor.update();           // collect sample and update rolling stats
    pulseRate = maxSensor.getBPM();
    spo2 = maxSensor.getSpO2();
  }

  // ---------------------
  // LCD: update displayed values every second
  // ---------------------
  if (now - lastDisplayUpdate >= DISPLAY_UPDATE_INTERVAL) {
    lastDisplayUpdate = now;
    displayValues(lcd, pulseRate, spo2); // your function to show values on LCD
  }

  // ---------------------
  // Bluetooth: send values periodically
  // ---------------------
  if (now - lastBTSend >= BT_SEND_INTERVAL) {
    lastBTSend = now;
    // compute a simple ECG percent from A0 (same mapping as before)
    int analogA0 = analogRead(A0);
    int ecgPercent = map(analogA0, 0, 700, 0, 100);
    if (ecgPercent < 0) ecgPercent = 0;
    if (ecgPercent > 100) ecgPercent = 100;

    sendData(ecgPercent, spo2, pulseRate); // HC-05 send (HC05Bluetooth module)
  }

  // No blocking delays here; loop continues smoothly
}
