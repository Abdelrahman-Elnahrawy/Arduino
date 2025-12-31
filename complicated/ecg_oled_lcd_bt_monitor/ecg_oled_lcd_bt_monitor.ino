/*
  Project: ECG OLED + LCD + HC-05 Pulse Oximeter Monitor (MAX30102)
  Board:   Arduino Uno / Nano (ATmega328P)
  Author:  Abdelrahman Elnahrawy
  License: MIT

  Description:
  - Draws a real-time ECG-like waveform from analog input A0 on a 128x64 SH1106 OLED using U8g2.
  - Shows Pulse (BPM) and SpO2 (%) values on a 16x2 I2C LCD.
  - Publishes a CSV line over Bluetooth via an HC-05 module connected to SoftwareSerial pins 10/11.
  - Reads MAX30102 (via SparkFun MAX30105 library) for IR/RED samples and estimates BPM/SpO2.

  Notes:
  - The BPM/SpO2 algorithm is intentionally simple and not medically accurate.
  - Ensure the correct I2C addresses for your LCD backpack (commonly 0x27 or 0x3F).
  - Uses non-blocking millis() scheduling for smooth drawing and updates.
*/

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <U8g2lib.h>
#include <MAX30105.h>
#include <SoftwareSerial.h>

// Modules
#include "src/display_lcd.h"
#include "src/display_oled.h"
#include "src/ecg_signal.h"
#include "src/max3010x_sensor.h"
#include "src/bt_hc05.h"

// -----------------------------
// Hardware configuration
// -----------------------------
// I2C LCD 16x2 address (adjust as needed: 0x27 or 0x3F are common)
static const uint8_t LCD_I2C_ADDR = 0x27; // change to 0x3F/0x20 if your module uses it
LiquidCrystal_I2C lcd(LCD_I2C_ADDR, 16, 2);

// OLED (SH1106 128x64) via U8g2, page-buffered variant
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// HC-05 Bluetooth (SoftwareSerial): D10=RX, D11=TX (connect HC-05 TX->D10, RX->D11 via divider)
SoftwareSerial bt_serial(10, 11);

// ECG analog input and buzzer output
static const uint8_t ECG_ANALOG_PIN = A0;
static const uint8_t BUZZER_PIN     = 8;

// -----------------------------
// Display layout
// -----------------------------
static const uint8_t SCREEN_WIDTH   = 128;
static const uint8_t SCREEN_HEIGHT  = 64;
static const uint8_t HEADER_HEIGHT  = 10;
static const uint8_t ECG_HEIGHT     = SCREEN_HEIGHT - HEADER_HEIGHT; // 54 px

// -----------------------------
// Scheduling (all in milliseconds)
// -----------------------------
static const unsigned long ECG_DRAW_INTERVAL_MS    = 10;   // ~100 Hz display refresh
static const unsigned long SENSOR_UPDATE_MS        = 200;  // 5 Hz MAX30102 read/compute
static const unsigned long LCD_UPDATE_MS           = 1000; // 1 Hz LCD refresh
static const unsigned long BT_UPDATE_MS            = 1000; // 1 Hz Bluetooth publish

unsigned long last_ecg_draw_ms   = 0;
unsigned long last_sensor_ms     = 0;
unsigned long last_lcd_ms        = 0;
unsigned long last_bt_ms         = 0;

// -----------------------------
// ECG drawing state
// -----------------------------
static const int ECG_ANALOG_MAX = 600; // Clip input to this range to scale nicely on OLED
int ecg_buffer[SCREEN_WIDTH];          // circular shift buffer across the screen width
int last_ecg_percent = 0;              // normalized percent (0..100) derived from last analog read

// -----------------------------
// MAX30102 sensor (SparkFun MAX30105 lib)
// -----------------------------
MAX30105 max_sensor;

int pulse_bpm = 0; // estimated BPM
int spo2_pct = 0;  // estimated SpO2

// -----------------------------
// Arduino lifecycle
// -----------------------------
void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Displays
  oled_welcome(u8g2);
  ecg_buffer_init(ecg_buffer, SCREEN_WIDTH, ECG_HEIGHT / 2);
  lcd_init_screen(lcd);

  // Sensors & Comm
  max3010x_begin(max_sensor);
  bt_begin(bt_serial);

  // Initial values
  pulse_bpm = 0;
  spo2_pct = 0;
}

void loop() {
  unsigned long now = millis();

  // ECG draw/update ~100 Hz
  if (now - last_ecg_draw_ms >= ECG_DRAW_INTERVAL_MS) {
    last_ecg_draw_ms = now;
    last_ecg_percent = ecg_update_from_analog(ecg_buffer, SCREEN_WIDTH, ECG_ANALOG_PIN,
                                              ECG_ANALOG_MAX, ECG_HEIGHT, BUZZER_PIN);
    ecg_draw_oled(u8g2, ecg_buffer, SCREEN_WIDTH, HEADER_HEIGHT, ECG_HEIGHT);
  }

  // MAX30102 update 5 Hz
  if (now - last_sensor_ms >= SENSOR_UPDATE_MS) {
    last_sensor_ms = now;
    max3010x_update_and_compute(max_sensor);
    pulse_bpm = max3010x_get_bpm();
    spo2_pct  = max3010x_get_spo2();
  }

  // LCD update 1 Hz
  if (now - last_lcd_ms >= LCD_UPDATE_MS) {
    last_lcd_ms = now;
    lcd_show_values(lcd, pulse_bpm, spo2_pct);
  }

  // Bluetooth publish 1 Hz
  if (now - last_bt_ms >= BT_UPDATE_MS) {
    last_bt_ms = now;
    bt_publish(bt_serial, last_ecg_percent, spo2_pct, pulse_bpm);
  }
}
