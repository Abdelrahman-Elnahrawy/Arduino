/*
 * Project: ECG Real-time Monitor with OLED & Bluetooth
 * Author: Abdelrahman Elnahrawy
 * Description: Captures analog ECG signals, visualizes the waveform on an 
 * SH1106 OLED display, provides audible heart-rate feedback via buzzer, 
 * and transmits telemetry data over Bluetooth.
 */

#include <U8g2lib.h>
#include <Wire.h>
#include <SoftwareSerial.h>

// --- Hardware Pins ---
#define ECG_INPUT_PIN A0
#define BUZZER_PIN    8
#define BT_RX         10
#define BT_TX         11

// --- Display Configuration ---
// SH1106 128x64 I2C
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define HEADER_HEIGHT 12
#define ECG_AREA_HEIGHT (SCREEN_HEIGHT - HEADER_HEIGHT)

// --- Communication ---
SoftwareSerial BT(BT_RX, BT_TX); 

// --- Global Buffer ---
int ecgBuffer[SCREEN_WIDTH];

/**
 * Initializes peripherals, shows a medical cohort welcome screen,
 * and fills the ECG buffer with baseline data.
 */
void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  BT.begin(9600);        // Default HC-05 Baud Rate
  u8g2.begin();

  // --- Splash Screen ---
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawStr(5, 15, "HNU - 2nd year");
    u8g2.drawStr(5, 30, "Medical Lab Cohort");
    
    // Draw a small "friendly" medical mascot/face
    u8g2.drawCircle(64, 50, 10);      // Face
    u8g2.drawDisc(60, 48, 1);         // Left Eye
    u8g2.drawDisc(68, 48, 1);         // Right Eye
    u8g2.drawLine(61, 55, 67, 55);    // Smile
  } while (u8g2.nextPage());

  delay(3000);

  // Initialize ECG buffer with middle-line value
  for (int i = 0; i < SCREEN_WIDTH; i++) {
    ecgBuffer[i] = ECG_AREA_HEIGHT / 2;
  }
}

/**
 * Main execution loop:
 * 1. Read Analog Signal -> 2. Process Buffer -> 3. Draw to OLED -> 4. Send BT Data
 */
void loop() {
  // 1. Read and Map Signal
  int rawAnalog = analogRead(ECG_INPUT_PIN);
  // Map 0-1023 range to the available height on the OLED
  int ecgValue = map(rawAnalog, 0, 1023, 0, ECG_AREA_HEIGHT - 1);

  // 2. Shift Buffer (Scrolling effect)
  for (int i = 0; i < SCREEN_WIDTH - 1; i++) {
    ecgBuffer[i] = ecgBuffer[i + 1];
  }
  ecgBuffer[SCREEN_WIDTH - 1] = ecgValue; 

  // 3. UI Rendering (OLED)
  u8g2.firstPage();
  do {
    // Draw Header
    u8g2.setFont(u8g2_font_5x7_tr);
    u8g2.drawStr(0, 8, "ECG LIVE | HNU MED LAB");
    u8g2.drawLine(0, 10, 127, 10); // Separator

    // Draw ECG Trace using Line Segments for smoothness
    for (int x = 0; x < SCREEN_WIDTH - 1; x++) {
      int y0 = SCREEN_HEIGHT - 1 - ecgBuffer[x];
      int y1 = SCREEN_HEIGHT - 1 - ecgBuffer[x + 1];
      u8g2.drawLine(x, y0, x + 1, y1);
    }
  } while (u8g2.nextPage());

  // 4. Threshold Logic & Feedback
  // If signal exceeds threshold (Potential QRS complex / beat)
  if (ecgValue > 35) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // 5. Bluetooth Telemetry
  // Format: E[BPM],[VAL]\n
  BT.print("E65,"); // Mock Heart Rate 65
  BT.print(ecgValue);
  BT.print("\n");
}