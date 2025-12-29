#include <U8g2lib.h>
#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11);  // RX, TX
// Constructor for SH1106 128x64 I2C (full buffer)
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
#define BUZZER 8
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define HEADER_HEIGHT 10
#define ECG_HEIGHT (SCREEN_HEIGHT - HEADER_HEIGHT)

int ecgBuffer[SCREEN_WIDTH];

void setup() {
  BT.begin(9600);         // HC-05 default baud rate
  u8g2.begin();
  // --- Welcome screen ---
  pinMode(BUZZER, OUTPUT);   // Set pin 8 as output
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawStr(5, 15, "HNU - 2nd year");
    u8g2.drawStr(5, 30, "Medical Lab Cohort");

    int faceX = 64;
    int faceY = 50;
    int faceR = 12;

    u8g2.drawCircle(faceX, faceY, faceR);
    u8g2.drawCircle(faceX - 5, faceY - 4, 2);
    u8g2.drawCircle(faceX + 5, faceY - 4, 2);
    u8g2.drawArc(faceX, faceY + 2, 5, 180, 0);
  } while (u8g2.nextPage());

  delay(3000);
  u8g2.clearBuffer();
  u8g2.sendBuffer();

  // Initialize ECG buffer
  for (int i = 0; i < SCREEN_WIDTH; i++) ecgBuffer[i] = ECG_HEIGHT / 2;

}

void loop() {
  // --- Read analog ECG value ---
  int analogValue = analogRead(A0);
  int ecgValue = map(analogValue, 0, 1023, 0, ECG_HEIGHT - 1);

  // --- Shift buffer left ---
  for (int i = 0; i < SCREEN_WIDTH - 1; i++) {
    ecgBuffer[i] = ecgBuffer[i + 1];
  }
  ecgBuffer[SCREEN_WIDTH - 1] = ecgValue; // newest value at right

  // --- Draw ECG ---
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_5x7_tr);
    u8g2.drawStr(0, 8, "ECG  HNU - 2nd year");

    for (int x = 0; x < SCREEN_WIDTH - 4; x++) {
      int y0 = HEADER_HEIGHT + ECG_HEIGHT - 1 - ecgBuffer[x];
      int y1 = HEADER_HEIGHT + ECG_HEIGHT - 1 - ecgBuffer[x + 1];
      u8g2.drawLine(x, y0, x + 1, y1);
    }
  } while (u8g2.nextPage());
if (ecgValue > 30)
{
  digitalWrite(BUZZER, HIGH);
}
else {
  digitalWrite(BUZZER, HIGH);
}
BT.print("E");
BT.print(65);
BT.print(",");
BT.print(ecgValue);
BT.print("\n");
}
