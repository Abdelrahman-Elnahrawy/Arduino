#include "ECGDisplay.h"
#define BUZZER_PIN 8  // choose any free digital pin
#define ECG_ANALOG_MAX 600  // choose any free digital pin
// ECG buffer
int ecgBuffer[SCREEN_WIDTH];

// Initialize ECG buffer
void initECG() {
  for (int i = 0; i < SCREEN_WIDTH; i++) ecgBuffer[i] = ECG_HEIGHT / 2;
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); // start off
}

// Read analog A0 and shift buffer
void updateECGBuffer() {
  int analogValue = analogRead(A0);
  if (analogValue > ECG_ANALOG_MAX) {analogValue = ECG_ANALOG_MAX;}
  int ecgValue = map(analogValue, 0, ECG_ANALOG_MAX, 0, ECG_HEIGHT - 1);
  if (ecgValue >= (ECG_HEIGHT * 0.6)) {  // top 20%
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }
  // Shift buffer left
  for (int i = 0; i < SCREEN_WIDTH - 1; i++) {
    ecgBuffer[i] = ecgBuffer[i + 1];
  }
  ecgBuffer[SCREEN_WIDTH - 1] = ecgValue; // newest value at right
}

// Draw ECG waveform and header
void drawECG() {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_5x7_tr);
    u8g2.drawStr(0, 8, "ECG  wave form :3");

    for (int x = 0; x < SCREEN_WIDTH - 4; x++) {
      int y0 = HEADER_HEIGHT + ECG_HEIGHT - 1 - ecgBuffer[x];
      int y1 = HEADER_HEIGHT + ECG_HEIGHT - 1 - ecgBuffer[x + 1];
      u8g2.drawLine(x, y0, x + 1, y1);
    }
  } while (u8g2.nextPage());
}
