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

// Minimal rolling buffers for naive BPM/SpO2 estimation
static const int MAX_SAMPLES = 25;
uint32_t ir_buffer[MAX_SAMPLES];
uint32_t red_buffer[MAX_SAMPLES];
int sample_index = 0;
bool buffer_filled = false;

int pulse_bpm = 0; // estimated BPM
int spo2_pct = 0;  // estimated SpO2

// -----------------------------
// Utility: clamp helper
// -----------------------------
template<typename T>
static T clamp_val(T v, T lo, T hi) {
  return (v < lo) ? lo : (v > hi) ? hi : v;
}

// -----------------------------
// LCD helpers
// -----------------------------
static inline bool is_valid_bpm(int x)  { return x >= 40 && x <= 200; }
static inline bool is_valid_spo2(int x) { return x >= 70 && x <= 100; }

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
  // Pulse
  lcd.setCursor(7, 0);
  lcd.print("   ");
  lcd.setCursor(7, 0);
  lcd.print(is_valid_bpm(bpm) ? String(bpm) : String("ERR"));

  // SpO2
  lcd.setCursor(7, 1);
  lcd.print("   ");
  lcd.setCursor(7, 1);
  lcd.print(is_valid_spo2(spo2) ? String(spo2) : String("ERR"));
}

// -----------------------------
// OLED helpers
// -----------------------------
void oled_welcome() {
  u8g2.begin();
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawStr(4, 14, "ECG + Pulse Oximeter");
    u8g2.drawStr(4, 30, "Arduino + SH1106 OLED");
    u8g2.drawStr(4, 46, "Author: A. Elnahrawy");
  } while (u8g2.nextPage());
  delay(1500);
}

void ecg_buffer_init() {
  for (int i = 0; i < SCREEN_WIDTH; i++) {
    ecg_buffer[i] = ECG_HEIGHT / 2; // midline
  }
}

void ecg_update_from_analog() {
  int analog_val = analogRead(ECG_ANALOG_PIN);
  if (analog_val > ECG_ANALOG_MAX) analog_val = ECG_ANALOG_MAX;

  // Map to OLED range and to percent for BT
  int ecg_val = map(analog_val, 0, ECG_ANALOG_MAX, 0, ECG_HEIGHT - 1);
  last_ecg_percent = map(analog_val, 0, ECG_ANALOG_MAX, 0, 100);
  last_ecg_percent = clamp_val(last_ecg_percent, 0, 100);

  // Simple buzzer gate for peaks (~top 40% of screen)
  digitalWrite(BUZZER_PIN, (ecg_val >= (int)(ECG_HEIGHT * 0.6)) ? HIGH : LOW);

  // Shift left and append newest sample at right
  for (int i = 0; i < SCREEN_WIDTH - 1; i++) {
    ecg_buffer[i] = ecg_buffer[i + 1];
  }
  ecg_buffer[SCREEN_WIDTH - 1] = ecg_val;
}

void ecg_draw_oled() {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_5x7_tr);
    u8g2.drawStr(0, 8, "ECG Waveform");

    // Draw continuous line across the buffer
    for (int x = 0; x < SCREEN_WIDTH - 1; x++) {
      int y0 = HEADER_HEIGHT + ECG_HEIGHT - 1 - ecg_buffer[x];
      int y1 = HEADER_HEIGHT + ECG_HEIGHT - 1 - ecg_buffer[x + 1];
      u8g2.drawLine(x, y0, x + 1, y1);
    }
  } while (u8g2.nextPage());
}

// -----------------------------
// MAX30102 simplified data handling
// -----------------------------
void max30102_begin() {
  // Initialize the SparkFun MAX30105 interface (works with MAX30102)
  if (!max_sensor.begin(Wire, I2C_SPEED_FAST)) {
    // Sensor not found; keep values at 0 and continue running
  }
  max_sensor.setup();
  max_sensor.setPulseAmplitudeRed(0x1F);
  max_sensor.setPulseAmplitudeIR(0x1F);
}

void max30102_update_and_compute() {
  // Read a single sample if available and update rolling buffers
  if (!max_sensor.available()) return;

  uint32_t ir = max_sensor.getIR();
  uint32_t red = max_sensor.getRed();

  ir_buffer[sample_index]  = ir;
  red_buffer[sample_index] = red;

  sample_index++;
  if (sample_index >= MAX_SAMPLES) {
    sample_index = 0;
    buffer_filled = true;
  }

  // Simple naive calculations when buffer filled
  if (buffer_filled) {
    // BPM: count rising zero-crossings around average IR value over the window
    long ir_sum = 0;
    for (int i = 0; i < MAX_SAMPLES; i++) ir_sum += ir_buffer[i];
    long ir_avg = ir_sum / MAX_SAMPLES;

    int beat_edges = 0;
    for (int i = 1; i < MAX_SAMPLES; i++) {
      if (ir_buffer[i - 1] < (uint32_t)ir_avg && ir_buffer[i] >= (uint32_t)ir_avg) {
        beat_edges++;
      }
    }
    // Assuming ~5 Hz sample window (SENSOR_UPDATE_MS = 200 ms per update)
    // MAX_SAMPLES cover ~5 seconds => scale beats over 5 s to per-minute
    // However, here we add one sample per SENSOR_UPDATE_MS (200ms => 5Hz)
    // MAX_SAMPLES=25 => 5s window => bpm = beats * 12
    pulse_bpm = beat_edges * 12;

    // SpO2: very naive ratio of averages (NOT ACCURATE)
    long red_sum = 0;
    for (int i = 0; i < MAX_SAMPLES; i++) red_sum += red_buffer[i];
    long red_avg = red_sum / MAX_SAMPLES;

    float ratio = (ir_avg > 0) ? ((float)red_avg / (float)ir_avg) : 1.0f;
    int est_spo2 = (int)(110.0f - (ratio * 25.0f));
    spo2_pct = clamp_val(est_spo2, 70, 100);
  }

  max_sensor.nextSample();
}

// -----------------------------
// Bluetooth publish helper
// -----------------------------
void bt_begin() {
  bt_serial.begin(9600); // HC-05 default baud
  delay(100);
  bt_serial.println("ECG+SpO2 Monitor Ready");
}

void bt_publish(int ecg_percent, int spo2, int bpm) {
  bt_serial.print("ECG:");
  bt_serial.print(ecg_percent);
  bt_serial.print("%,SpO2:");
  bt_serial.print(spo2);
  bt_serial.print("%,BPM:");
  bt_serial.println(bpm);
}

// -----------------------------
// Arduino lifecycle
// -----------------------------
void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Displays
  oled_welcome();
  ecg_buffer_init();
  lcd_init_screen();

  // Sensors & Comm
  max30102_begin();
  bt_begin();

  // Initial values
  pulse_bpm = 0;
  spo2_pct = 0;
}

void loop() {
  unsigned long now = millis();

  // ECG draw/update ~100 Hz
  if (now - last_ecg_draw_ms >= ECG_DRAW_INTERVAL_MS) {
    last_ecg_draw_ms = now;
    ecg_update_from_analog();
    ecg_draw_oled();
  }

  // MAX30102 update 5 Hz
  if (now - last_sensor_ms >= SENSOR_UPDATE_MS) {
    last_sensor_ms = now;
    max30102_update_and_compute();
  }

  // LCD update 1 Hz
  if (now - last_lcd_ms >= LCD_UPDATE_MS) {
    last_lcd_ms = now;
    lcd_show_values(pulse_bpm, spo2_pct);
  }

  // Bluetooth publish 1 Hz
  if (now - last_bt_ms >= BT_UPDATE_MS) {
    last_bt_ms = now;
    bt_publish(last_ecg_percent, spo2_pct, pulse_bpm);
  }
}
