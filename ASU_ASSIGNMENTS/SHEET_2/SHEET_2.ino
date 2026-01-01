/**************************************************************
 * Introduction to Embedded Systems – ASU Course
 * ------------------- SHEET 2 -------------------
 *
 * To compile or test any task:
 * 👉 Uncomment ONLY the required section
 *
 * Author: Abdelrahman Elnahrawy
 *************************************************************/


/* ============================================================
 * SHEET 2 – TASK 1
 * PWM via 8-bit DIP Switch
 * ============================================================
 * Notes:
 * - For Proteus simulation, connect pull-down resistors
 *   to DIP switch pins
 */

/*
#define LED_PIN 13
int DIP_PINS[8] = {2,3,4,5,6,7,8,9};

float pwm_value = 0;
float old_value = 0;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 8; i++) {
    pinMode(DIP_PINS[i], INPUT);
  }

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  pwm_value = 0;

  for (int i = 0; i < 8; i++) {
    pwm_value += digitalRead(DIP_PINS[i]) * pow(2, i);
  }

  if (pwm_value != old_value) {
    analogWrite(LED_PIN, pwm_value);
    old_value = pwm_value;
  }
}
*/


/* ============================================================
 * SHEET 2 – TASK 2
 * Blink LED using Interrupts & Timers
 * ============================================================
 * Version 1: WITH Interrupts
 */

/*
#define LED_PIN  13
#define BTN_DOWN 2
#define BTN_UP   3

int blink_factor = 0;

void decrease() {
  blink_factor--;
  if (blink_factor < 0) blink_factor = 0;
}

void increase() {
  blink_factor++;
  if (blink_factor > 10) blink_factor = 10;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_UP, INPUT);
  pinMode(BTN_DOWN, INPUT);

  attachInterrupt(digitalPinToInterrupt(BTN_UP), increase, RISING);
  attachInterrupt(digitalPinToInterrupt(BTN_DOWN), decrease, RISING);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(blink_factor * 500);
  digitalWrite(LED_PIN, LOW);
  delay(blink_factor * 500);
}
*/


/* ============================================================
 * SHEET 2 – TASK 2
 * Version 2: WITHOUT Interrupts
 * ============================================================
 */

/*
#define LED_PIN 13
#define BTN_DOWN 2
#define BTN_UP   3

int blink_factor = 1;
unsigned long timer = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_UP, INPUT);
  pinMode(BTN_DOWN, INPUT);
}

void loop() {

  if (digitalRead(BTN_UP)) {
    delay(50);
    if (digitalRead(BTN_UP)) {
      blink_factor++;
      if (blink_factor > 10) blink_factor = 10;
      while (digitalRead(BTN_UP));
    }
  }

  if (digitalRead(BTN_DOWN)) {
    delay(50);
    if (digitalRead(BTN_DOWN)) {
      blink_factor--;
      if (blink_factor < 1) blink_factor = 1;
      while (digitalRead(BTN_DOWN));
    }
  }

  if (millis() - timer > 500 * blink_factor) {
    digitalWrite(LED_PIN, HIGH);
  }

  if (millis() - timer > 1000 * blink_factor) {
    digitalWrite(LED_PIN, LOW);
    timer = millis();
  }
}
*/


/* ============================================================
 * SHEET 2 – TASK 3
 * Binary Counter (0 → 255)
 * ============================================================
 */

/*
int LEDS[] = {2,3,4,5,6,7,8,9,10};
unsigned int counter = 0;

void setup() {
  for (int i = 0; i < 9; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
}

void loop() {
  counter++;
  if (counter > 255) counter = 0;

  for (int i = 0; i < 9; i++) {
    digitalWrite(LEDS[i], counter & (1 << i));
  }

  delay(1000);
}
*/


/* ============================================================
 * SHEET 2 – TASK 4
 * Analog Play (Interrupt-controlled ADC source)
 * ============================================================
 */

/*
#define LED_PIN 13
int analog_channel = 0;

void switch_channel() {
  analog_channel++;
  if (analog_channel > 5) analog_channel = 0;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), switch_channel, RISING);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(analogRead(analog_channel) / 2);
  digitalWrite(LED_PIN, LOW);
  delay(analogRead(analog_channel) / 2);
}
*/


/* ============================================================
 * SHEET 2 – TASK 5
 * Analog Read LED Chaser
 * ============================================================
 */

/*
int LEDS[] = {2,3,4,5,6,7,8,9,10,11,12};

void setup() {
  for (int i = 0; i < 11; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 11; i++) {
    digitalWrite(LEDS[i], HIGH);
    delay(analogRead(A0));
    digitalWrite(LEDS[i], LOW);
  }
}
*/


/* ============================================================
 * SHEET 2 – TASK 7
 * LOMAD EL FARA7 😄
 * Button controlled LED + Blink Mode
 * ============================================================
 */

/*
const int BUTTON_PIN = 2;
const int LED_PIN    = 13;

bool led_state = HIGH;
bool blink_mode = false;

unsigned long blink_timer = 0;
unsigned long press_time  = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, led_state);
}

void loop() {

  if (digitalRead(BUTTON_PIN) == LOW) {
    press_time = millis();

    while (digitalRead(BUTTON_PIN) == LOW);

    if (millis() - press_time > 80) {
      led_state = !led_state;
      digitalWrite(LED_PIN, led_state);
    }

    if (millis() - press_time > 5000) {
      blink_mode = !blink_mode;
    }
  }

  if (blink_mode && millis() - blink_timer > 400) {
    led_state = !led_state;
    digitalWrite(LED_PIN, led_state);
    blink_timer = millis();
  }
}
*/
