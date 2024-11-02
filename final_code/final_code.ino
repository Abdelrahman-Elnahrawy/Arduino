#include <LiquidCrystal.h>
#include <FreeRTOS.h>
#include <task.h>

// Define stepper motor pins
#define stepPin 3
#define dirPin 4
#define enablePin 5
#define MAXSPEED 1200
#define MINSPEED 0.5
int cursorColumn;

// Define LCD pin connections
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Motor control variables
int mode = 0; // Mode 0 for select screen, Mode 1 for speed, Mode 2 for angle
float angle = 0; // For angle control
float speed = 0; // For speed control (steps per second)
const int stepsPerRev = 200; // Steps per revolution for the motor

// Button pins (from LCD shield)
int buttonState;
#define btnRIGHT  1
#define btnUP     2
#define btnDOWN   3
#define btnLEFT   4
#define btnSELECT 5

// Control type selection
int selectedOption = 0; // 0 for SPEED, 1 for ANGLE

// Function prototypes for tasks
void vLCDTask(void *pvParameters);
void vStepperTask(void *pvParameters);
void vEncoderTask(void *pvParameters);

void setup() {
  Serial.begin(115200);

  // Set up stepper motor pins
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  
  // Enable the stepper driver
  digitalWrite(enablePin, LOW); // LOW to enable

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.cursor(); // Show cursor
  lcd.blink();  // Make cursor blink

  // Create FreeRTOS tasks
  xTaskCreate(vLCDTask, "LCD Task", 1000, NULL, 1, NULL);
  xTaskCreate(vStepperTask, "Stepper Task", 1000, NULL, 1, NULL);
  xTaskCreate(vEncoderTask, "Encoder Task", 1000, NULL, 1, NULL);

  // Start the scheduler
  vTaskStartScheduler();
}

void loop() {
  // No need for code in loop when using FreeRTOS
}

// Task for LCD display and button handling
void vLCDTask(void *pvParameters) {
  while (1) {
    buttonState = read_LCD_buttons();
    if (mode == 0) {
      if (buttonState == btnRIGHT || buttonState == btnLEFT) {
        selectedOption = !selectedOption;
        displayControlType();
      } else if (buttonState == btnSELECT) {
        mode = selectedOption + 1; // 1 for SPEED, 2 for ANGLE
        displayMenu();
      }
    }

    // Let the task run every 200ms
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

// Task for controlling the stepper motor
void vStepperTask(void *pvParameters) {
  while (1) {
    if (mode == 1) {  // Speed mode
      stepMotorRun(speed);
    } else if (mode == 2) {  // Angle mode
      stepmotorang(angle);
    }

    // Delay task execution (you can adjust this based on motor control needs)
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

// Task for handling the encoder inputs
void vEncoderTask(void *pvParameters) {
  while (1) {
    // Read encoder values here and adjust speed/angle
    // This is a placeholder for encoder logic
    // Add actual code to read from the encoder and adjust speed or angle accordingly

    // Delay task execution for smooth handling
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

// Function to display control type
void displayControlType() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" CONTROL TYPE");

  // Display "SPEED" and "ANGLE" with one highlighted
  lcd.setCursor(0, 1);
  if (selectedOption == 0) {
    lcd.print("> SPEED  ");
    lcd.print("  ANGLE ");
  } else {
    lcd.print("  SPEED  ");
    lcd.print("> ANGLE ");
  }
}

// Function to display the current mode
void displayMenu() {
  lcd.clear();
  if (mode == 1) {
    lcd.setCursor(0, 0);
    lcd.print("   Speed Mode");
  } else if (mode == 2) {
    lcd.setCursor(0, 0);
    lcd.print("   Angle Mode");
  }
}

// Stepper motor angle control
void stepmotorang(uint16_t angle) {
  // Implement motor control logic for angle mode
}

// Stepper motor speed control
void stepMotorRun(uint16_t speed) {
  // Implement motor control logic for speed mode
}

// Function to read buttons
int read_LCD_buttons() {
  int button = -1;
  if (analogRead(0) < 1000) {
    delay(70);  // Debouncing delay
    int adc_key_in = analogRead(0);
    if (adc_key_in < 1000) {
      if (adc_key_in < 100) { 
        button = btnRIGHT;
      } else if (adc_key_in < 300) {
        button = btnUP;
      } else if (adc_key_in < 500) {
        button = btnDOWN;
      } else if (adc_key_in < 700) {
        button = btnLEFT;
      } else if (adc_key_in < 900) {
        button = btnSELECT;
      }
    }

    while (analogRead(0) < 1000) {  // Wait for button release
      delay(100);
    }
  }

  return button;
}
