#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SparkFun_MAX3010x.h>

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change 0x27 to 0x20 or 0x3F if needed

// ---------------- MAX30102 Sensor ----------------
MAX30105 particleSensor;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Init LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MAX30102 Test");

  delay(1000);

  // Init MAX30102
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30102 NOT FOUND!");
    lcd.setCursor(0,1);
    lcd.print("Sensor FAIL");
    while (1);
  }

  // Sensor configuration (BEST STABLE SETTINGS)
  particleSensor.setup(
    0x1F,   // LED Brightness 6.2mA
    4,      // Sample average 4
    2,      // LED mode = Red + IR
    100,    // Sample rate 100 Hz
    411,    // Pulse width 411us
    4096    // ADC range
  );

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("BPM: ---  SpO2: --");
}

void loop() {
  // Read raw values
  long irValue  = particleSensor.getIR();
  long redValue = particleSensor.getRed();

  // Show on Serial
  Serial.print("IR=");
  Serial.print(irValue);
  Serial.print("  RED=");
  Serial.print(redValue);

  // Compute HR + SpO2 using built-in library functions
  int bpm = particleSensor.getHeartRate();
  int spo2 = particleSensor.getSpO2();

  Serial.print("  BPM=");
  Serial.print(bpm);
  Serial.print("  SpO2=");
  Serial.println(spo2);

  // Show on LCD
  lcd.setCursor(0,0);
  lcd.print("BPM:");
  lcd.print(bpm);
  lcd.print("   ");   // clear old digits

  lcd.setCursor(0,1);
  lcd.print("SpO2:");
  lcd.print(spo2);
  lcd.print("%   ");

  delay(100); // stable & smooth
}
