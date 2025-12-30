/**
 * PROJECT: I2C Pulse Oximeter & Heart Rate Monitor
 * AUTHOR: Abdelrahman Elnahrawy
 * DESCRIPTION: Real-time BPM and SpO2 monitoring using the MAX30102 sensor.
 * Features I2C LCD integration and proximity-based data filtering.
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SparkFun_MAX3010x.h>

// --- Configuration ---
LiquidCrystal_I2C lcd(0x27, 16, 2); 
MAX30105 particleSensor;

// Threshold to detect if a finger is actually on the sensor
const long FINGER_THRESHOLD = 50000; 

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("MAX30102 Init...");

  // Initialize MAX30102
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println(F("MAX30102 was not found. Please check wiring/power."));
    lcd.clear();
    lcd.print("Sensor Error!");
    while (1);
  }

  // Optimized Sensor Settings
  byte ledBrightness = 0x1F; // 6.2mA
  byte sampleAverage = 4;    // 4 samples
  byte ledMode = 2;          // Red + IR
  int sampleRate = 100;      // 100Hz
  int pulseWidth = 411;      // 411us
  int adcRange = 4096;       // 4096 range

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
  
  lcd.clear();
  lcd.print("Place Finger...");
}

void loop() {
  long irValue = particleSensor.getIR();

  // 1. Check if finger is present
  if (irValue < FINGER_THRESHOLD) {
    lcd.setCursor(0, 0);
    lcd.print("BPM:  --  No Obj");
    lcd.setCursor(0, 1);
    lcd.print("SpO2: --        ");
    Serial.println(F("No finger detected."));
  } 
  else {
    // 2. Fetch processed data
    int bpm = (int)particleSensor.getHeartRate();
    int spo2 = (int)particleSensor.getSpO2();

    // 3. Update LCD (Only if data is valid)
    lcd.setCursor(0, 0);
    lcd.print("BPM: ");
    lcd.print(bpm > 0 ? String(bpm) : "---");
    lcd.print("    "); // Clear old digits

    lcd.setCursor(0, 1);
    lcd.print("SpO2: ");
    lcd.print(spo2 > 0 ? String(spo2) + "%" : "---");
    lcd.print("    ");

    // 4. Serial Debugging
    Serial.print(F("IR: ")); Serial.print(irValue);
    Serial.print(F(" | BPM: ")); Serial.print(bpm);
    Serial.print(F(" | SpO2: ")); Serial.println(spo2);
  }

  delay(250); // Refresh rate for readability
}