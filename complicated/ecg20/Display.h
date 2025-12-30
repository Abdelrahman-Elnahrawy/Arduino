#pragma once
#include "Validation.h"  
// Initialize the LCD screen
void displayInit(LiquidCrystal_I2C &lcd) {
  lcd.setCursor(0, 0);
  lcd.print("Pulse:     BPM");

  lcd.setCursor(0, 1);
  lcd.print("SpO2 :     %");
}

// Display values or ERR
void displayValues(LiquidCrystal_I2C &lcd, int pulse, int spo2) {

  // Pulse
  lcd.setCursor(7, 0);
  lcd.print("   ");
  lcd.setCursor(7, 0);

  if (isPulseValid(pulse)) {
    lcd.print(pulse);
  } else {
    lcd.print("ERR");
  }

  // SpO2
  lcd.setCursor(7, 1);
  lcd.print("   ");
  lcd.setCursor(7, 1);

  if (isSpO2Valid(spo2)) {
    lcd.print(spo2);
  } else {
    lcd.print("ERR");
  }
}
