/**
 * @file PWMPin11.h
 * @brief PWM Control for Pin 11 on Arduino Uno
 * 
 * This module provides functions to initialize and control PWM (Pulse Width Modulation) on Pin 11 
 * (OC2A) of the Arduino Uno. The PWM signal can be configured for different frequencies and duty cycles.
 * 
 * The module works by configuring Timer 2 in CTC (Clear Timer on Compare Match) mode, allowing precise 
 * control over the PWM signal characteristics. The frequency and duty cycle can be adjusted dynamically 
 * based on application requirements.
 * 
 * Features:
 * - Initialize PWM on Pin 11.
 * - Set frequency and duty cycle for the PWM signal.
 * - Enable and disable PWM output.
 * 
 * Connections:
 * - Pin 11: Connected to the output device for PWM control.
 * 
 * Usage:
 * - Call `PWMPin11Init()` to initialize PWM on Pin 11.
 * - Use `setPWMPin11(frequency, dutyCycle)` to set the desired frequency (in Hz) and duty cycle (0 to 100%).
 * - Call `enablePWMPin11()` to start the PWM output.
 * - Call `disablePWMPin11()` to stop the PWM output.
 */




uint16_t TargetPulsesCount ;
uint16_t CurrentPulsesCount ;
uint8_t prescalerBits = 0;
void (*OnCompareAInterruptFun)() = &OncompareAinterruptCasePWM;
void OncompareAinterruptCasePulses(){
    digitalWrite(11, HIGH); // Reset the pin (turn off)
  CurrentPulsesCount++;
  if(CurrentPulsesCount>=TargetPulsesCount){
        TIMSK2 &= ~(1 << OCIE2A); // Disable interrupt on OCR2A match
        DisablePWMPin11();
        CurrentPulsesCount = 0; 
  }
}
void OncompareAinterruptCasePWM(){
  digitalWrite(11, HIGH); // Reset the pin (turn off)
}

// Function to initialize PWM on Pin 11
void PWMPin11Init() {
    pinMode(11, OUTPUT);  // Set Pin 11 as an output pin

    // Set Timer2 in CTC mode and stop it
    TCCR2A = 0;
    TCCR2B = 0;

    // Set CTC mode with OCR2A as TOP
    TCCR2A |= (1 << WGM21);  // Configure Timer2 for CTC mode
   // TCCR2A |= (1 << COM2A1)|(1 << COM2A0); // set pin 11 , OC2A on compare match  
    TIMSK2 |= (1 << OCIE2B)|(1 << OCIE2A);
}

// Function to set PWM frequency and duty cycle
void setPWMPin11(float frequency, float dutyCycle) {
    // Calculate the required TOP value for the desired frequency
    unsigned long topValue;

    if(frequency == 0) {return;}
    // Find the smallest prescaler that will fit the desired frequency
    if (frequency >= 62500) {
        // Prescaler = 1
        prescalerBits = (1 << CS20);
        topValue = (16000000 / (1 *  frequency)) - 1;
    } else if (frequency >= 7813) {
        // Prescaler = 8
        prescalerBits = (1 << CS21);
        topValue = (16000000 / (8 *  frequency)) - 1;
    } else if (frequency >= 1954) {
        // Prescaler = 32
        prescalerBits = (1 << CS21) | (1 << CS20);
        topValue = (16000000 / (32 *  frequency)) - 1;
    } else if (frequency >= 977) {
        // Prescaler = 64
        prescalerBits = (1 << CS22);
        topValue = (16000000 / (64 *  frequency)) - 1;
    } else if (frequency >= 489) {
        // Prescaler = 128
        prescalerBits = (1 << CS22) | (1 << CS20);
        topValue = (16000000 / (128 *  frequency)) - 1;
    } else if (frequency >= 245) {
        // Prescaler = 256
        prescalerBits = (1 << CS22) | (1 << CS21);
        topValue = (16000000 / (256 *  frequency)) - 1;
    } else {
        // Prescaler = 1024
        prescalerBits = (1 << CS22) | (1 << CS21) | (1 << CS20);
        topValue = (16000000 / (1024 *  frequency)) - 1;
    }

    // Limit the topValue to a maximum of 255 (8-bit timer)
    if (topValue > 255) {
        topValue = 255;
    }

    // Calculate OCR2B for the duty cycle
    unsigned long compareValue = ((dutyCycle * (topValue + 1)) / 100);

    // Set the TOP value and compare value
    OCR2A = topValue;       // Set TOP for frequency
    OCR2B = compareValue;   // Set Compare value for duty cycle

    // Set the Timer2 prescaler
    TCCR2B = prescalerBits;

}

// Function to enable PWM output
void EnablePWMPin11() {
    TCCR2B |= prescalerBits; // Start Timer2 with prescaler of 1 (or previous configuration)
}

// Function to disable PWM output
void DisablePWMPin11() {
  TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20)); // Stop Timer2 by clearing all clock select bits
}

void generatePWMPulses(int numPulses, float frequency, float dutyCycle) {
  if(frequency == 0 | dutyCycle == 0) return;
   DisablePWMPin11();
    CurrentPulsesCount = 0;
    TargetPulsesCount = numPulses;
    // Enable Output Compare Match A Interrupt
    setPWMPin11(frequency, dutyCycle);
    OnCompareAInterruptFun = &OncompareAinterruptCasePulses;
    EnablePWMPin11();
}

ISR(TIMER2_COMPA_vect) {
(*OnCompareAInterruptFun)();
}

  ISR(TIMER2_COMPB_vect) {
    digitalWrite(11, LOW); // Reset the pin (turn off)
 }
void setup(){
  Serial.begin(115200);
  PWMPin11Init();
}
void loop(){

setPWMPin11(30, 50);
delay(2000);
setPWMPin11(50, 50);
delay(2000);
setPWMPin11(100, 50);
delay(2000);
setPWMPin11(700, 50);
delay(2000);
setPWMPin11(1000, 50);
delay(2000);
setPWMPin11(3000, 50);
delay(2000);
setPWMPin11(9000, 50);
delay(2000);
setPWMPin11(10000, 50);
delay(2000);
setPWMPin11(30000, 50);
delay(2000);
setPWMPin11(50000, 50);
delay(2000);
setPWMPin11(90000, 50);
delay(2000);
setPWMPin11(100000, 50);
delay(2000);
setPWMPin11(300000, 50);
delay(2000);
setPWMPin11(500000, 50);
delay(2000);
setPWMPin11(900000, 50);
delay(2000);
setPWMPin11(1000000, 50);
delay(2000);
setPWMPin11(15000000, 50);
delay(2000);
setPWMPin11(2666666, 50);
delay(2000);

}