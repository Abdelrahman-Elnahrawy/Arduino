/*
 * Project: ESP8266 Multi-Relay Hub with Analog Button Ladder
 * Author: Abdelrahman Elnahrawy
 * Features: 
 * - Single-pin ($A0$) Multi-button Interface
 * - 6-Channel Relay Control (5 Digital, 1 PWM)
 * - MQTT Status Reporting (including Temperature)
 * - PIR Motion Interrupts
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// --- Hardware Mapping ---
const int PIR_PIN    = 2;  // D4
const int MOD_RELAY  = 4;  // D2 (Switches A0 between Buttons and Temp Sensor)
const int RELAYS[]   = {12, 13, 14, 15, 0}; // D6, D7, D5, D8, D3
const int PWM_RELAY  = 16; // D0

// ... (WiFi and MQTT setup logic remains consistent with your previous modules) ...

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  unsigned long now = millis();

  // --- Task 1: Periodic Temperature Reading ---
  // Uses a relay to switch the A0 pin input source
  if(now - temp_time > 600000) { // Every 10 minutes
    temp_time = now;
    digitalWrite(MOD_RELAY, HIGH); 
    delay(50); // Stabilization delay
    t = analogRead(A0) / 10.0;
    digitalWrite(MOD_RELAY, LOW);
  }

  // --- Task 2: Analog Button Ladder Logic ---
  button = analogRead(A0);
  if(now - button_time > 700 && button < 1024) {
    button_time = now;
    processButtons(button);
  }

  // --- Task 3: MQTT Telemetry ---
  if (now - lastMsg > 2000) {
    sendTelemetry(now);
  }
}

void processButtons(int val) {
  if(val >= 400 && val < 500) toggleRelay(0);      // Button 1 -> Relay 1
  else if(val > 150 && val < 300) toggleRelay(1); // Button 2 -> Relay 2
  else if(val > 600 && val < 700) toggleRelay(2); // Button 3 -> Relay 3
  else if(val > 750 && val < 900) toggleRelay(3); // Button 4 -> Relay 4
  else if(val > 0   && val < 100) toggleRelay(4); // Button 5 -> Relay 5
  else if(val > 900 && val < 1020) {              // Button 6 -> PWM Increase
    R6 = (R6 >= 255) ? 0 : R6 + 25;
    analogWrite(PWM_RELAY, R6);
  }
}