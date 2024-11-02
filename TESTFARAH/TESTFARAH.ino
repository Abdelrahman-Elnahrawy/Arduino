void setup() {
  // Set the pin mode for digital output
  pinMode(9, OUTPUT); // First PWM output pin
  pinMode(10, OUTPUT); // Second PWM output pin
}

void loop() {
  // Frequency: 50 kHz, Period: 1/50,000 = 0.00002 seconds = 20 microseconds
  // Duty cycle: 50% (10 microseconds HIGH, 10 microseconds LOW)

  // Set the first pin HIGH
  digitalWrite(9, HIGH);

  // Optional delay to introduce a phase shift between the two PWM signals
  delayMicroseconds(2); // Adjust this delay to achieve the desired phase shift

  // Set the second pin HIGH
  digitalWrite(10, HIGH);

  // Set the first pin LOW
  delayMicroseconds(8); // Remaining time for the first PWM signal
  digitalWrite(9, LOW);

  // Set the second pin LOW after a slight delay
  delayMicroseconds(2); // Delay between PWM signals
  digitalWrite(10, LOW);
  delayMicroseconds(8); // Remaining time for the second PWM signal
}