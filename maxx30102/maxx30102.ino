#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 particleSensor;

// Variables to hold measurements
float bpm;
float spO2;

// For measuring loop timing
uint32_t irValue;

// Function to check if a beat was detected
void checkPulse() {
  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true) {
    bpm = getBeatsPerMinute();
  }
}

// Function to calculate SpO2 (simplified)
void calculateSpO2() {
  long redValue = particleSensor.getRed();
  long irValue = particleSensor.getIR();

  int readings = 100; // number of samples
  static int redArr[100], irArr[100];
  static int index = 0;

  redArr[index] = redValue;
  irArr[index] = irValue;
  index = (index + 1) % readings;

  int redSum = 0, irSum = 0;
  for (int i = 0; i < readings; i++) {
    redSum += redArr[i];
    irSum += irArr[i];
  }

  // ratio of ratios method (very simplified for test)
  float ratio = (float)redSum / (float)irSum;
  spO2 = 110 - 25 * ratio; // rough estimate
  if (spO2 > 100) spO2 = 100;
  if (spO2 < 70) spO2 = 70;
}

void setup() {
  Serial.begin(115200);
  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("MAX30102 was not found. Check wiring!");
    while (1);
  }

  // Setup sensor with default values
  particleSensor.setup(); // default settings
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeIR(0x0A);

  Serial.println("MAX30102 test starting...");
}

void loop() {
  checkPulse();       // get BPM
  calculateSpO2();    // get SpO2

  // Print results
  Serial.print("BPM: ");
  Serial.print(bpm);
  Serial.print("   SpO2: ");
  Serial.println(spO2);

  delay(1000); // update every second
}
