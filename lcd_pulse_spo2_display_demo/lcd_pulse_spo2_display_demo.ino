/*
  Project: LCD Pulse/SpO2 Display Demo
  Board:   Arduino Uno / Nano (ATmega328P)
  Author:  Abdelrahman Elnahrawy
  License: MIT

  Description:
  - Minimal demonstration for showing Pulse (BPM) and SpO2 (%) values on a 16x2 I2C LCD.
  - Includes validation of displayed values with graceful "ERR" indicators when out of range.
  - Currently generates demo values periodically; replace with sensor reads for real measurements.

  Notes:
  - Adjust the LCD I2C address to match your backpack (commonly 0x27 or 0x3F).
  - The data source is mocked via random() to exercise UI and validation.
*/

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// -----------------------------
// LCD configuration
// -----------------------------
static const uint8_t LCD_I2C_ADDR = 0x27; // Change to 0x3F/0x20 if needed
LiquidCrystal_I2C lcd(LCD_I2C_ADDR, 16, 2);

// -----------------------------
// Update interval
// -----------------------------
static const unsigned long DISPLAY_UPDATE_MS = 1000; // 1 Hz update
unsigned long last_update_ms = 0;

// -----------------------------
// Demo values (replace with real sensor inputs)
// -----------------------------
int pulse_bpm = 75;
int spo2_pct  = 98;

// -----------------------------
// Validation helpers
// -----------------------------
static inline bool is_valid_bpm(int x)  { return x >= 40 && x <= 200; }
static inline bool is_valid_spo2(int x) { return x >= 70 && x <= 100; }

// -----------------------------
// LCD helpers
// -----------------------------
void lcd_init_screen() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Pulse:     BPM");

  lcd.setCursor(0, 1);
  lcd.print("SpO2 :     %");
}

void lcd_show_values(int bpm, int spo2) {
  // Pulse display
  lcd.setCursor(7, 0);
  lcd.print("   "); // clear previous digits
  lcd.setCursor(7, 0);
  lcd.print(is_valid_bpm(bpm) ? String(bpm) : String("ERR"));

  // SpO2 display
  lcd.setCursor(7, 1);
  lcd.print("   "); // clear previous digits
  lcd.setCursor(7, 1);
  lcd.print(is_valid_spo2(spo2) ? String(spo2) : String("ERR"));
}

// -----------------------------
// Arduino lifecycle
// -----------------------------
void setup() {
  lcd_init_screen();
  randomSeed(analogRead(A0)); // seed randomness for demo values
}

void loop() {
  unsigned long now = millis();

  if (now - last_update_ms >= DISPLAY_UPDATE_MS) {
    last_update_ms = now;

    // Update displayed values
    lcd_show_values(pulse_bpm, spo2_pct);

    // Demo: change values to exercise validation (remove/replace with sensor reads)
    pulse_bpm = random(30, 210); // intentionally extends beyond valid bounds to show ERR
    spo2_pct  = random(60, 102); // intentionally extends beyond valid bounds to show ERR
  }
}
