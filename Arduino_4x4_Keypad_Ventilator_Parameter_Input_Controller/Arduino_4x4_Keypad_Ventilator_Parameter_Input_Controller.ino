#include <Keypad.h>

/*
 --------------------------------------------------
 Arduino 4x4 Keypad Ventilator Parameter Controller
 --------------------------------------------------
 This code allows the user to enter ventilator
 parameters using a 4x4 matrix keypad:
 - Oxygen percentage
 - Maximum pressure (MP)
 - Respiratory rate
 - Tidal volume
 - Ventilation mode
 - I/E ratio
 --------------------------------------------------
*/

// ---------------- Keypad Configuration ----------------
const byte ROWS = 4;
const byte COLS = 4;

// Keypad layout
char keys[ROWS][COLS] = {
  {'1','2','3','a'},
  {'4','5','6','b'},
  {'7','8','9','c'},
  {'*','0','#','d'}
};

// Arduino pins connected to keypad
byte rowPins[ROWS] = {9, 8, 7, 6};   // Rows
byte colPins[COLS] = {5, 4, 3, 2};   // Columns

// Create keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ---------------- System Variables ----------------

// Ventilator operating mode
int mode = 1;

// Digit position helper for numeric entry
int x = 2;

// Temporary number accumulator
int S = 0;

// Ventilator parameters
float oxygen = 21;   // Oxygen percentage
float MP     = 25;   // Maximum pressure
float rate   = 15;   // Breathing rate
float volume = 500;  // Tidal volume (ml)
int   ratio  = 1;    // I/E ratio

// Input type selector
// 1 = Oxygen
// 2 = Pressure
// 3 = Rate
// 4 = Volume
int IT = 0;

// Timing control for input timeout
unsigned long previousMillis0 = 0;

// ---------------- Setup ----------------
void setup() {
  Serial.begin(9600);
}

// ---------------- Main Loop ----------------
void loop() {

  unsigned long currentMillis0 = millis();

  // Read keypad key
  int key = keypad.getKey() - 48;

  // -------- Select Parameter to Edit --------
  if (key == 49) { IT = 1; x = 2; S = 0; previousMillis0 = currentMillis0; } // '1' Oxygen
  if (key == 50) { IT = 2; x = 2; S = 0; previousMillis0 = currentMillis0; } // '2' Pressure
  if (key == 51) { IT = 3; x = 2; S = 0; previousMillis0 = currentMillis0; } // '3' Rate
  if (key == 52) { IT = 4; x = 2; S = 0; previousMillis0 = currentMillis0; } // '4' Volume

  // Change ventilation mode using '*'
  if (key == 42) {
    mode++;
    if (mode > 4) mode = 1;
  }

  // Change I/E ratio using '#'
  if (key == 35) {
    ratio++;
    if (ratio > 3) ratio = 1;
  }

  // -------- Oxygen Input --------
  if (IT == 1) {
    if (key >= 0 && key <= 9) {
      S = S + 1 + key * pow(10, x);
      S = (S / 10) * 10;
      x--;
      oxygen = S / 10;
      previousMillis0 = currentMillis0;
      Serial.print("Oxygen: ");
      Serial.println(oxygen);
    }

    if (oxygen < 21)  oxygen = 21;
    if (oxygen > 100) oxygen = 100;

    if (currentMillis0 - previousMillis0 >= 1500) {
      IT = 0; x = 2; S = 0;
    }
  }

  // -------- Pressure Input --------
  if (IT == 2) {
    if (key >= 0 && key <= 9) {
      S = S + 1 + key * pow(10, x);
      S = (S / 10) * 10;
      x--;
      MP = S / 10;
      previousMillis0 = currentMillis0;
      Serial.print("Pressure: ");
      Serial.println(MP);
    }

    if (MP < 10) MP = 10;
    if (MP > 37) MP = 37;

    if (currentMillis0 - previousMillis0 >= 1500) {
      IT = 0; x = 2; S = 0;
    }
  }

  // -------- Rate Input --------
  if (IT == 3) {
    if (key >= 0 && key <= 9) {
      S = S + 1 + key * pow(10, x);
      S = (S / 10) * 10;
      x--;
      rate = S / 10;
      previousMillis0 = currentMillis0;
      Serial.print("Rate: ");
      Serial.println(rate);
    }

    if (rate < 10) rate = 10;
    if (rate > 30) rate = 30;

    if (currentMillis0 - previousMillis0 >= 1500) {
      IT = 0; x = 2; S = 0;
    }
  }

  // -------- Volume Input --------
  if (IT == 4) {
    if (key >= 0 && key <= 9) {
      S = S + 1 + key * pow(10, x);
      S = (S / 10) * 10;
      x--;
      volume = S;
      previousMillis0 = currentMillis0;
      Serial.print("Volume: ");
      Serial.println(volume);
    }

    if (volume < 270) volume = 270;
    if (volume > 800) volume = 800;

    if (currentMillis0 - previousMillis0 >= 1500) {
      IT = 0; x = 2; S = 0;
    }
  }
}
