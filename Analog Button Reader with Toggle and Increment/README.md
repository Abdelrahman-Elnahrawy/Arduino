# 🎛️ Analog Button Reader — Toggle & Increment

![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino-orange) ![Language: C/C++](https://img.shields.io/badge/Language-C%2B%2B-blue) ![Status: Example](https://img.shields.io/badge/Status-Example-brightgreen)

A compact, user-friendly example that shows how to read multiple buttons using a single analog input (resistor ladder), and implement two behaviors: toggle (on/off) and increment (cycle value).

Emojis and colored badges included for readability ✨🔋🔘

---

## Project goal
- Demonstrate how to wire multiple buttons to one analog pin using a resistor ladder.
- Provide code for two interaction modes:
  - Toggle: press to toggle a state (e.g., LED on/off)
  - Increment: press to advance a numeric value or mode
- Offer debouncing and stable analog reading tips.

---

## Why use analog button reading?
- Saves digital pins when you have many buttons
- Simple resistor ladder converts each button press to a different voltage
- Works well for menus, mode selection, and compact UIs

---

## Hardware required
- Arduino Uno / Nano / compatible
- 4–6 momentary push buttons
- Resistors for ladder (e.g., 4.7k, 10k, 22k — example values given below)
- Breadboard and jumper wires
- Optional: LED or display to show state/value

Suggested resistor ladder (example for 4 buttons):
- Button 1 -> 10k to A0
- Button 2 -> 4.7k to A0
- Button 3 -> 2.2k to A0
- Button 4 -> 1k to A0
- Other side of all buttons -> 5V; analog pin A0 connected to resistor network that goes to GND through a known pull-down (or use internal pull-down logic where supported)

Note: exact resistor values depend on desired voltage spacing and ADC tolerance.

---

## Wiring (high level)
- Construct resistor ladder so each button closes a unique voltage divider to analog pin A0.
- Connect the analog pin to the junction of the ladder and read ADC (0–1023 on a 10-bit ADC).
- Use a common ground between Arduino and ladder.

A simple approach: connect the buttons between 5V and ladder nodes; ladder bottom to GND; A0 reads the node voltages when buttons are pressed.

---

## Behavior details
- Toggle mode: a short press toggles a boolean state (e.g., LED on/off). Long-press or repeat handling can be added.
- Increment mode: each press advances a numeric value (wraps at max). Useful for settings/menus.

---

## Example Arduino sketch
This example reads an analog value on A0 and maps it to button indexes. It includes debouncing and a simple mode switch between Toggle and Increment.

```cpp
// Analog button reader example
const uint8_t ANALOG_PIN = A0;
const uint8_t LED_PIN = 13;

// Thresholds (0..1023) for 4 buttons — tune to your resistor values
const int buttonThresholds[] = {100, 300, 500, 700};
const uint8_t NUM_BUTTONS = sizeof(buttonThresholds) / sizeof(buttonThresholds[0]);

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; // ms
int lastButton = -1;

bool toggleState = false;
int incrementValue = 0;

enum Mode {MODE_TOGGLE, MODE_INCREMENT};
Mode currentMode = MODE_TOGGLE;

int readButton() {
  int val = analogRead(ANALOG_PIN);
  for (uint8_t i = 0; i < NUM_BUTTONS; ++i) {
    if (val < buttonThresholds[i]) return i;
  }
  return -1; // no button
}

void handleButtonPress(int btn) {
  // Map button index to actions
  if (btn == 0) {
    // Toggle mode select
    currentMode = MODE_TOGGLE;
  } else if (btn == 1) {
    // Increment mode select
    currentMode = MODE_INCREMENT;
  } else if (btn == 2) {
    // Primary action button
    if (currentMode == MODE_TOGGLE) {
      toggleState = !toggleState;
      digitalWrite(LED_PIN, toggleState ? HIGH : LOW);
    } else {
      incrementValue = (incrementValue + 1) % 10; // example range 0..9
    }
  } else if (btn == 3) {
    // Secondary action: reset
    incrementValue = 0;
    toggleState = false;
    digitalWrite(LED_PIN, LOW);
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  analogReadResolution ? void() : void(); // compatibility placeholder
}

void loop() {
  int btn = readButton();
  if (btn != lastButton) {
    lastDebounceTime = millis();
    lastButton = btn;
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    static int lastHandled = -1;
    if (btn != -1 && btn != lastHandled) {
      handleButtonPress(btn);
      lastHandled = btn;
    } else if (btn == -1) {
      lastHandled = -1; // released
    }
  }

  // Optional: tiny delay to reduce ADC churn
  delay(10);
}
```

Notes:
- Tune `buttonThresholds` to match your resistor ladder measured ADC values.
- For more reliable readings, average multiple analogRead() samples.
- If using many buttons, consider using an I2C ADC or multiplexer.

---

## Improvements & tips
- Use proper pull-down/up resistors to avoid floating states.
- Add long-press detection and hold-repeat for incrementing quickly.
- Show current value on an LCD/OLED for better UX.

---

## License & Author
- Author: Abdelrahman Elnahrawy
- Recommended license: MIT

