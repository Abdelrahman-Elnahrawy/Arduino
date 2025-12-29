#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Display.h"
#include "Validation.h"

LiquidCrystal_I2C lcd(0x20, 16, 2);

// Variables coming from MAX30102
int pulseRate = 75;
int spo2 = 98;

unsigned long lastUpdate = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  displayInit(lcd);   // from Display.h
}

void loop() {

  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();

    // Update values on the LCD
    displayValues(lcd, pulseRate, spo2);

    // Testing only — remove when using real sensor
    pulseRate = random(30, 210);
    spo2 = random(60, 102);
  }
}
