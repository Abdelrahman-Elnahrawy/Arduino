/**
 * PROJECT: Precision LCD Clock with Auto-Backlight
 * AUTHOR: Abdelrahman Elnahrawy
 * DESCRIPTION: An accurate clock using internal millis() timing. Features 
 * a 15-second backlight timeout and manual time-set buttons.
 */

#include "LiquidCrystal.h"

// --- Pin Definitions ---
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int pin_contrast  = 9;   // PWM Contrast
const int pin_backlight = 10;  // PWM Backlight
const int pin_hour_set  = 0;   // Button: Hours
const int pin_min_set   = 1;   // Button: Minutes

// --- Display Constants ---
const int DEFAULT_CONTRAST  = 100;
const int DEFAULT_BACKLIGHT = 120;
const int BACKLIGHT_TIMEOUT = 150; // ~30 seconds (150 * 200ms)

// --- Global Time Variables ---
int h = 12, m = 59, s = 45;
int is_pm = 1; // 0 = AM, 1 = PM
int bl_timer = BACKLIGHT_TIMEOUT;

static uint32_t last_time = 0;
uint32_t now = 0;

void update_display() {
  lcd.setCursor(0, 0);
  lcd.print("Time ");
  if (h < 10) lcd.print("0");
  lcd.print(h);
  lcd.print(":");
  if (m < 10) lcd.print("0");
  lcd.print(m);
  lcd.print(":");
  if (s < 10) lcd.print("0");
  lcd.print(s);
  lcd.print(is_pm ? " PM" : " AM");

  lcd.setCursor(0, 1);
  lcd.print("Precision clock ");
}

void setup() {
  lcd.begin(16, 2);
  pinMode(pin_hour_set, INPUT_PULLUP);
  pinMode(pin_min_set, INPUT_PULLUP);

  analogWrite(pin_contrast, DEFAULT_CONTRAST);
  analogWrite(pin_backlight, DEFAULT_BACKLIGHT);
  
  update_display();
  now = millis();
}

void loop() {
  // We divide 1 second into 5 chunks of 200ms for button responsiveness
  for (int i = 0; i < 5; i++) {
    while ((millis() - last_time) < 200) {
      yield(); // Keep background tasks alive
    }
    last_time = millis();

    // Read Input
    int btn_h = digitalRead(pin_hour_set);
    int btn_m = digitalRead(pin_min_set);

    // --- Backlight Logic ---
    if (bl_timer > 0) {
      bl_timer--;
      if (bl_timer == 0) analogWrite(pin_backlight, 0);
    }

    // Wake backlight on button press
    if ((btn_h == LOW || btn_m == LOW)) {
      if (bl_timer == 0) {
        bl_timer = BACKLIGHT_TIMEOUT;
        analogWrite(pin_backlight, DEFAULT_BACKLIGHT);
        while(digitalRead(pin_hour_set) == LOW || digitalRead(pin_min_set) == LOW); // Wait for release
      } else {
        // Increment time if already awake
        if (btn_h == LOW) { h++; bl_timer = BACKLIGHT_TIMEOUT; }
        if (btn_m == LOW) { m++; s = 0; bl_timer = BACKLIGHT_TIMEOUT; }
        delay(200); // Simple debounce
      }
    }

    // --- Overflow Management ---
    if (s >= 60) { s = 0; m++; }
    if (m >= 60) { m = 0; h++; }
    if (h > 12)  { h = 1; is_pm = !is_pm; }

    update_display();
  }

  s++; // End of 1000ms cycle
}