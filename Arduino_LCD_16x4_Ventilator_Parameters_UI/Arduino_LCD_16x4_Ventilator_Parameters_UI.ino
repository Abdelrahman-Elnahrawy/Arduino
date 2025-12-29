#include <LiquidCrystal.h>

/*
  --------------------------------------------------
  Arduino LCD 16x4 Ventilator Parameters UI
  --------------------------------------------------
  Displays ventilator parameters on a 16x4 LCD:
  - Pressure
  - Oxygen percentage
  - Respiratory rate
  - Volume
  - I/E ratio
  --------------------------------------------------
*/

// LCD pin connections
// rs, en, d4, d5, d6, d7
const int rs = 12;
const int en = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

/*
 LCD wiring notes:
 - V0   -> Potentiometer (contrast)
 - LEDA -> Potentiometer / +5V via resistor
 - RW   -> GND
 - VSS  -> GND
 - VDD  -> +5V
 */

// Create LCD object (16 columns, 4 rows)
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// ------------------- Parameters -------------------

// Maximum pressure (cmH2O)
int MP = 15;

// Display strings for ventilation modes
char *myStrings[]  = {"Pressure A", "Pressure", "Volume A", "Volume"};
char *myStrings1[] = {"1:1", "1:2", "1:3"};   // I/E ratios

// Current operating parameters
int mode   = 2;     // Mode index
int oxygen = 21;    // Oxygen percentage
int rate   = 15;    // Breathing rate
int ratio  = 1;     // I/E ratio index
int volume = 500;   // Tidal volume (ml)

// Error flag (must be defined elsewhere in real system)
bool ERORR = false;

// ------------------- Setup -------------------
void setup() {

  // Initialize LCD
  lcd.begin(16, 4);

  /*
    Pre-fill LCD with fixed labels.
    Extra characters are intentionally written
    to avoid flickering during updates.
  */
  lcd.print(
    "pressure:  cm."
    "HOO2%:  % "
    "rate:   "
    "AAAAAAA"
    "mode:           "
    "V:    ml "
    "I/E:   "
  );
}

// ------------------- Main Loop -------------------
void loop() {

  // -------- Error Display --------
  if (ERORR) {

    // Display alarm message when leakage or error occurs
    lcd.setCursor(0, 0);
    lcd.print(
      "XXXXXXXXXXXXXXXX"
      "LECKAAAAAAAAAGE"
      "XXXXXXXXXXXXXXXX"
    );
  }

  // -------- Normal Operation --------
  else {

    // Display pressure value
    lcd.setCursor(9, 0);
    lcd.print(MP);

    // Display ventilation mode
    lcd.setCursor(5, 1);
    lcd.print(myStrings[mode]);

    // Display oxygen percentage
    lcd.setCursor(4, 2);
    lcd.print(oxygen);

    // Display breathing rate
    lcd.setCursor(13, 2);
    lcd.print(rate);

    // Display tidal volume
    lcd.setCursor(2, 3);
    lcd.print(volume);

    // Display I/E ratio
    lcd.setCursor(13, 3);
    lcd.print(myStrings1[ratio]);
  }
}
