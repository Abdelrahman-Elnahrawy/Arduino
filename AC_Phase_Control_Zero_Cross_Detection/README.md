# ⚡ AC Phase Control — Zero Cross Detection

![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino-orange) ![Language: C/C++](https://img.shields.io/badge/Language-C%2B%2B-blue) ![Status: Example](https://img.shields.io/badge/Status-Example-brightgreen)

A compact project to control the phase angle of an AC load using a TRIAC and zero-cross detection. This lets you dim incandescent heaters/lights or control motor power by delaying the TRIAC trigger after each AC zero-crossing.

Emojis & color make docs friendlier 🎛️🔌🔥

---

## Project goal
- Detect AC mains zero crossing.
- Fire a TRIAC after a selectable delay (phase angle) to control power.
- Provide a simple, safe-to-follow example sketch and wiring notes for hobbyist learning.

---

## WARNING — Safety first ❗⚠️
This project works with mains AC voltage. Working on mains is dangerous and can be lethal.
- Do NOT build or test on live mains unless you understand mains safety, isolation methods, and local regulations.
- Use isolation (optocouplers) for both TRIAC drive (MOC302x family) and zero-cross detection where possible.
- Use fuses, RCD/GFCI, proper insulating enclosures, and a mains-rated TRIAC and components.

The author is not responsible for any damage or injury.

---

## Features
- Zero-cross detection (interrupt-driven)
- Adjustable phase delay (brightness / power level input)
- Minimal example Arduino sketch included
- Notes for wiring and components

---

## Hardware required
- Arduino Uno / Nano / compatible
- TRIAC (e.g., BTA16 or similar, mains-rated)
- Opto-triac driver (e.g., MOC3021) for gate isolation
- Zero-cross detection: optocoupler or resistor divider + clamp + isolation
- Gate resistor (100Ω–330Ω), snubber network (if needed), fuse, mains-rated connectors
- Small breadboard/testing rig (but use final proper PCB/enclosure for anything permanent)
- Optional: potentiometer to adjust brightness, push buttons, LED for status

Suggested example pins (change as needed):
- ZERO_CROSS_PIN -> D2 (INT0)
- TRIAC_GATE_PIN -> D9

---

## Wiring (high level)
- Mains Live (L) -> TRIAC MT1
- TRIAC MT2 -> Load -> Mains Neutral (N)
- TRIAC gate -> through gate resistor -> opto-triac output (or direct when using appropriate isolation)
- Arduino output -> opto-triac input (with proper resistor)
- Zero-cross detector -> isolated input to Arduino interrupt (D2). Prefer using an optocoupler for isolation.

Note: Do not connect the Arduino directly to mains without proper isolation circuitry.

---

## How it works (short)
1. On every zero crossing of the AC waveform the zero-cross circuit signals the Arduino (interrupt).
2. The Arduino calculates a delay based on desired power/brightness.
3. After the delay, it pulses the TRIAC gate (through the opto-triac) to conduct for the remainder of the half-cycle.
4. On the next zero crossing the TRIAC turns off naturally and the cycle repeats.

---

## Example Arduino sketch (minimal)
This is a simple educational example. Do not rely on it for safety-critical systems.

```cpp
// Minimal example: zero cross detection + phase delay firing
const uint8_t ZC_PIN = 2;     // Interrupt pin, zero-cross detector
const uint8_t TRIAC_PIN = 9;  // TRIAC gate driver output
volatile bool zcDetected = false;
volatile unsigned long lastZcMicros = 0;

void IRAM_ATTR zcISR() {
  zcDetected = true;
  lastZcMicros = micros();
}

void setup() {
  pinMode(TRIAC_PIN, OUTPUT);
  digitalWrite(TRIAC_PIN, LOW);
  pinMode(ZC_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(ZC_PIN), zcISR, RISING);
}

void loop() {
  // brightness 0..100 (0 = off, 100 = full)
  static int brightness = 50;
  // map brightness to delay (microseconds)
  const unsigned long minDelay = 100;      // near full conduction
  const unsigned long maxDelay = 8000;     // near cutoff (for 50Hz half-cycle ~10000us)
  unsigned long delayUs = map(brightness, 0, 100, maxDelay, minDelay);

  if (zcDetected) {
    // Wait desired phase delay then fire
    unsigned long firedAt = lastZcMicros + delayUs;
    while (micros() < firedAt) { /* busy wait; acceptable for small demos */ }
    // Pulse TRIAC gate for short time
    digitalWrite(TRIAC_PIN, HIGH);
    delayMicroseconds(200); // gate pulse width
    digitalWrite(TRIAC_PIN, LOW);
    zcDetected = false;
  }

  // Example: change brightness slowly (demo)
  static unsigned long t = millis();
  if (millis() - t > 200) {
    t = millis();
    brightness = (brightness + 1) % 101;
  }
}
```

Notes:
- For 50 Hz mains, one half-cycle ≈ 10,000 µs; for 60 Hz ≈ 8,333 µs — tune delays accordingly.
- Use opto-isolation for both the TRIAC driver and zero-cross detection input for safety.

---

## Tuning & Improvements
- Use hardware timer for finer timing and avoid busy-wait in ISR context.
- Debounce/filter zero-cross input; protect against spikes.
- Add closed-loop or adaptive dimming depending on load type.
- Implement soft-start to reduce inrush.

---

## Troubleshooting
- No dimming: verify zero-cross pulses and TRIAC gate pulses with an isolated oscilloscope.
- Flicker: incorrect timing, noisy zero-cross signal, or mains frequency mismatch.
- TRIAC failing to latch: gate resistor too large, load type incompatible, missing snubber.

---

## License & Author
- Author: Abdelrahman Elnahrawy (repository owner)
- Suggested license: MIT (add LICENSE file if you want permissive usage)

---

If you'd like, I can:
- Generate a wiring diagram image (SVG) or a more detailed schematic.
- Tune the example for 60Hz or for specific TRIAC/opto parts.
- Produce the next README for the next project folder.
