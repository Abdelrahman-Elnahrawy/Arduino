#include "display_oled.h"

void oled_welcome(U8G2 &u8g2) {
  u8g2.begin();
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x12_tr);
    u8g2.drawStr(4, 14, "ECG + Pulse Oximeter");
    u8g2.drawStr(4, 30, "Arduino + SH1106 OLED");
    u8g2.drawStr(4, 46, "Author: A. Elnahrawy");
  } while (u8g2.nextPage());
}

void ecg_draw_oled(U8G2 &u8g2, const int *buffer, uint8_t width, uint8_t header_h, uint8_t ecg_h) {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_5x7_tr);
    u8g2.drawStr(0, 8, "ECG Waveform");
    for (uint8_t x = 0; x < (uint8_t)(width - 1); x++) {
      int y0 = header_h + ecg_h - 1 - buffer[x];
      int y1 = header_h + ecg_h - 1 - buffer[x + 1];
      u8g2.drawLine(x, y0, x + 1, y1);
    }
  } while (u8g2.nextPage());
}
