#include "OLEDDisplay.h"

// Define the OLED object
//U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
// Initialize OLED and show welcome screen
void initOLED() {
  u8g2.begin();

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawStr(5, 15, "HMU - 2nd year");
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
  clearOLED();
}

// Clear OLED display
void clearOLED() {
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}