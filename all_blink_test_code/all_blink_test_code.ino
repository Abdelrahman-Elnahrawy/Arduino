/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/

void setup() {
  pinMode(16, OUTPUT); 
    pinMode(5, OUTPUT);
      pinMode(4, OUTPUT);
        pinMode(0, OUTPUT);
          pinMode(2, OUTPUT);
            pinMode(14, OUTPUT);
              pinMode(12, OUTPUT);
                pinMode(13, OUTPUT);
                  pinMode(15, OUTPUT);
                  pinMode(3, OUTPUT);
                  pinMode(1, OUTPUT);// Initialize the LED_BUILTIN pin as an output
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(16, LOW); 
  digitalWrite(5, LOW); 
  digitalWrite(4, LOW); 
  digitalWrite(0, LOW); 
  digitalWrite(2, LOW); 
  digitalWrite(14, LOW); 
  digitalWrite(12, LOW); 
  digitalWrite(13, LOW); 
  digitalWrite(15, LOW); 
  digitalWrite(3, LOW);
  digitalWrite(1, LOW); // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(16, HIGH); 
  digitalWrite(5, HIGH); 
  digitalWrite(4, HIGH); 
  digitalWrite(0, HIGH); 
  digitalWrite(2, HIGH); 
  digitalWrite(14, HIGH); 
  digitalWrite(12, HIGH); 
  digitalWrite(13, HIGH); 
  digitalWrite(15, HIGH); 
  digitalWrite(3, HIGH);
  digitalWrite(1, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
}
