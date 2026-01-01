# 💡 Button-Controlled LED — Long-Press Blink

![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino-orange) ![Language: C/C++](https://img.shields.io/badge/Language-C%2B%2B-blue) ![Status: Example](https://img.shields.io/badge/Status-Example-brightgreen)

A simple, beginner-friendly project that demonstrates controlling an LED with a button that has two behaviors:
- Short press: toggle LED on/off
- Long press: enable a blinking mode

Emojis and colored badges added for readability — great for quick demos and learning input handling on Arduino 🎉🔘

---

## Project goal
- Teach button reading with debouncing.
- Implement short-press vs long-press detection.
- Control an LED with toggle and blinking modes.

---

## Hardware required
- Arduino Uno / Nano / compatible  
- Momentary push button  
- 10kΩ resistor (pull-down or use internal pull-up)  
- LED + 220Ω resistor (or use built-in LED on pin 13)  
- Breadboard and jumper wires

Optional:
- Use a transistor (NPN) if you drive a larger LED strip or external load.

---

## Wiring (high level)
- Button between input pin and GND/5V depending on pull-up/pull-down approach.
  - Recommended: use INPUT_PULLUP and wire button to GND (simpler wiring).
- LED anode -> digital output pin (220Ω) -> GND via resistor; or use built-in LED on pin 13.

Example (using internal pull-up):
- BUTTON_PIN -> one side of button; other side of button -> GND.
- On press, the pin reads LOW.

---

## Behavior
- Short press (< longPressThreshold): toggles LED on/off.
- Long press (>= longPressThreshold): enters blinking mode (LED blinks at blinkInterval).
- Release from long press returns to previous or a default state (configurable).

---

## Example Arduino sketch
This sketch uses the internal pull-up (button to GND), debouncing, and long-press detection.

```cpp
// Button-controlled LED with short press (toggle) and long press (blink) behavior

const uint8_t BUTTON_PIN = 2;   // button input (use a pin that supports interrupt if desired)
const uint8_t LED_PIN = 13;     // built-in LED

// Timing
const unsigned long debounceDelay = 50;       // ms
const unsigned long longPressThreshold = 800; // ms to consider long press
const unsigned long blinkInterval = 300;      // ms blink period when in blink mode

// State tracking
int buttonState = HIGH;            // current reading (INPUT_PULLUP -> HIGH when released)
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long pressStartTime = 0;
bool pressedHandled = false;

bool ledOn = false;
bool blinkMode = false;
unsigned long lastBlinkToggle = 0;
bool blinkLedState = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // button to GND
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    // reset debounce timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // stable state
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        // button pressed
        pressStartTime = millis();
        pressedHandled = false;
      } else {
        // button released
        unsigned long pressDuration = millis() - pressStartTime;
        if (pressDuration < longPressThreshold) {
          // short press: toggle LED (and exit blink mode)
          blinkMode = false;
          ledOn = !ledOn;
          digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
          Serial.println("Short press — toggled LED");
        } else {
          // long press released: stop blink mode
          blinkMode = false;
          blinkLedState = false;
          digitalWrite(LED_PIN, LOW);
          ledOn = false;
          Serial.println("Long press released — stopped blinking");
        }
      }
    } else {
      // if currently pressed, check for long press entry
      if (buttonState == LOW && !pressedHandled) {
        if (millis() - pressStartTime >= longPressThreshold) {
          // Enter blink mode
          blinkMode = true;
          pressedHandled = true; // ensure we only enter once per press
          ledOn = false;
          Serial.println("Long press — entering blink mode");
        }
      }
    }
  }

  // Blink handling
  if (blinkMode) {
    if (millis() - lastBlinkToggle >= blinkInterval) {
      lastBlinkToggle = millis();
      blinkLedState = !blinkLedState;
      digitalWrite(LED_PIN, blinkLedState ? HIGH : LOW);
    }
  }

  lastButtonState = reading;
}
```

Notes:
- Adjust `longPressThreshold` and `blinkInterval` to taste.
- Using interrupts for button press detection is possible but often unnecessary for simple projects; debounced polling is sufficient.
- For multiple buttons or advanced UI, consider a state machine or menu library.

---

## Improvements & ideas
- Add double-press detection or multi-press gestures.
- Add LED patterns (fade, PWM) instead of simple on/off blink — use analogWrite on PWM pins.
- Use a small OLED or LCD to show current mode and settings.
- Persist preferred mode using EEPROM so device remembers last state.

---

## License & Author
- Author: Abdelrahman Elnahrawy  
- Suggested license: MIT


