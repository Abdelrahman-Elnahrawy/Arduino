/*
  Project: LM35 Temperature Controlled Fan (PWM)
  Course : Introduction to Embedded Systems
  Sheet  : Sheet 4 – Question 1
  Author : Abdelrahman Elnahrawy

  Description:
  - Reads temperature from LM35 sensor (analog)
  - Controls fan speed using PWM
  - Fan is OFF below 20°C
  - Fan is OFF above 40°C
  - Fan speed increases linearly between 20°C and 40°C
*/

#define FAN_PIN 3          // PWM pin connected to the fan (via transistor/driver)
#define LM35_PIN A0        // Analog pin connected to LM35 output

int adcValue = 0;          // Raw ADC reading
float temperature = 0.0;   // Temperature in Celsius

void setup() {
  pinMode(FAN_PIN, OUTPUT);   // Set fan pin as output
}

void loop() {
  // Read analog value from LM35
  adcValue = analogRead(LM35_PIN);

  /*
    LM35 output:
    - 10mV per °C
    - ADC reference = 5V
    - ADC resolution = 1024

    Temperature calculation:
    Voltage = (adcValue / 1024) * 5000 (mV)
    Temperature (°C) = Voltage / 10
  */
  temperature = ((adcValue / 1024.0) * 5000.0) / 10.0;

  // Fan control logic
  if (temperature < 20) {
    // Fan OFF below 20°C
    digitalWrite(FAN_PIN, LOW);
  }
  else if (temperature > 40) {
    // Fan OFF above 40°C (safety limit)
    digitalWrite(FAN_PIN, LOW);
  }
  else {
    /*
      Linear PWM control between 20°C and 40°C

      Example:
      20°C -> PWM = 0
      30°C -> PWM = 127
      40°C -> PWM = 255
    */
    int pwmValue = ((temperature - 20) * 255) / 20;
    analogWrite(FAN_PIN, pwmValue);
  }
}
