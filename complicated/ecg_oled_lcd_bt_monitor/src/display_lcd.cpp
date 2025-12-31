#include "display_lcd.h"

// Local validation helpers
static inline bool is_valid_bpm(int x)  { return x >= 40 && x <= 200; }
static inline bool is_valid_spo2(int x) { return x >= 70 && x <= 100; }

void lcd_init_screen(LiquidCrystal_I2C &lcd) {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Pulse:     BPM");

  lcd.setCursor(0, 1);
  lcd.print("SpO2 :     %");
}

void lcd_show_values(LiquidCrystal_I2C &lcd, int bpm, int spo2) {
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
