# MAX30102_LiquidCrystal_Display

Arduino sketch to read **Heart Rate (BPM)** and **Oxygen Saturation (SpO2)** from a **MAX30102 sensor** and show the results on a **16x2 I2C LCD**.

## Features
- Reads **IR and Red LED signals** from MAX30102
- Computes **BPM** and **SpO2 (%)**
- Displays results on **16x2 LCD**
- Prints raw and computed values to **Serial Monitor**
- Uses **SparkFun MAX3010x library**

## Hardware_Connections
- MAX30102 → I2C pins (SDA, SCL)
- LCD 16x2 I2C → I2C pins (SDA, SCL)
- Default I2C addresses:
  - LCD: `0x27`
  - MAX30102: default in library (`0x57`)

## How_It_Works
1. Initialize LCD and MAX30102 sensor
2. Check if sensor is detected; halt if not
3. Read raw IR and Red values
4. Compute BPM and SpO2
5. Show BPM on first LCD line, SpO2 on second line
6. Print values to Serial Monitor for debugging

## Use_Cases
- Heart rate & SpO2 monitoring projects
- Wearable health devices
- Fitness and medical hobbyist applications

⚠️ **Ensure proper sensor placement** (finger or earlobe) for accurate readings.
