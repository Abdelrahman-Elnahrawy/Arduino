// Arduino PWM Signal Generator 1Hz - 1MHz
// Output on D9, configurable via Serial Monitor
// Min on/off time: 0.2µs, duty cycle 0-100%

#include <TimerOne.h>

// Default settings
unsigned long t = 1000;      // Period in microseconds (default 1000 μs -> 1000 Hz)
unsigned long k = 512;       // Duty cycle value for Timer1 (default 50%)
unsigned long f;             // Frequency input from serial
unsigned long dutyCycle = 50; // Duty cycle input from serial

// Limits
const unsigned long maxFrequency = 1000000; // 1 MHz
const unsigned long minFrequency = 1;       // 1 Hz
const unsigned long maxDutyCycle = 100;     // 100%
const unsigned long minDutyCycle = 0;       // 0%
const float MIN_ON_TIME = 0.2;              // Minimum on/off time in microseconds

void setup() {
  delay(1000); // Prevent serial garbage
  Serial.begin(115200);
  Serial.println("Signal generator 1Hz-1MHz, 0-100% dutycycle, min Ton/Toff 0.2µs");
  pinMode(9, OUTPUT);
  setPWM(); // Apply default PWM
}

void loop() {
  readFrequency();    // Read frequency from Serial Monitor
  readDutycycle();    // Read duty cycle from Serial Monitor
  checkOnOfftime();   // Ensure on/off times are within limits
  setPWM();           // Update PWM output
}

// Read frequency input from Serial Monitor
void readFrequency() {
  Serial.print("Enter Frequency 1 to 1000000 [Hz]: ");
  while (Serial.available() == 0); // Wait for input
  String input = Serial.readStringUntil('\n');
  Serial.println(input + " Hz");
  f = input.toInt();

  if (f >= minFrequency && f <= maxFrequency) {
    t = 1000000 / f; // Convert frequency to period (μs)
  } else {
    Serial.println("Frequency is out of range! Please try again");
    readFrequency(); // Retry input
  }
}

// Read duty cycle input from Serial Monitor
void readDutycycle() {
  Serial.print("Enter Dutycycle 0 to 100 [%]: ");
  while (Serial.available() == 0);
  String input = Serial.readStringUntil('\n');
  Serial.println(input + " %");
  dutyCycle = input.toInt();

  if (dutyCycle >= minDutyCycle && dutyCycle <= maxDutyCycle) {
    k = (dutyCycle * 1024) / 100; // Convert to Timer1 scale
  } else {
    Serial.println("Dutycycle is out of range! Please try again");
    readDutycycle(); // Retry input
  }
}

// Check if on/off times are valid
void checkOnOfftime() {
  float onTimeMicros = 1000000.0f * ((dutyCycle / 100.0f) / f);
  float offTimeMicros = 1000000.0f * ((1 - (dutyCycle / 100.0f)) / f);

  if (onTimeMicros >= MIN_ON_TIME && offTimeMicros >= MIN_ON_TIME || offTimeMicros == 0 || onTimeMicros == 0) {
    Serial.println("Output updated to:");
    Serial.print("Frequency: "); Serial.print(f); Serial.print("Hz, ");
    Serial.print("Dutycycle: "); Serial.print(dutyCycle); Serial.print("%, ");
    Serial.print("Ton: "); Serial.print(onTimeMicros); Serial.print("µs, ");
    Serial.print("Toff: "); Serial.print(offTimeMicros); Serial.println("µs");
    setPWM();
  } else {
    Serial.println("On/Off-Time too short. Please try again");
  }
}

// Set PWM output using Timer1
void setPWM() {
  Timer1.initialize(t);  // Set period
  Timer1.pwm(9, k);      // Set duty cycle on pin D9
}
