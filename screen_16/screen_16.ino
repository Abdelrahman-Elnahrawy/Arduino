#include <LiquidCrystal.h>
#include "Display_Handler.h"

// Motor settings
#define STEPS_PER_REV 200           // Motor steps per revolution
#define MAX_SPEED 9200              // Max speed for the motor
#define MIN_SPEED 0.5               // Min speed for the motor

// Stepper motor control pins
#define STEP_PIN 3
#define DIR_PIN 4
#define ENABLE_PIN 5

// Rotation direction
#define CLOCKWISE         0
#define COUNTER_CLOCKWISE 1

// LCD button pin definitions (from LCD shield)
#define BUTTON_RIGHT  1
#define BUTTON_UP     2
#define BUTTON_DOWN   3
#define BUTTON_LEFT   4
#define BUTTON_SELECT 5
#define BUTTON_NULL   0

// Control modes
#define MODE_SPEED     0
#define MODE_ANGLE     1
#define MODE_SELECTION 2

// LCD configuration
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Variables for control and display
bool isLocked = false;

float motorSpeed = 0;
float motorAngle = 0;
int lcdCursorPos = 7;
int selectedControl = MODE_SELECTION;
bool rotationDir = CLOCKWISE;
bool CurrentSelection ;
// Function prototypes

void controlMotor();
void setMotorSpeed(uint16_t speed, bool Direction);
void setMotorAngle(uint16_t angle, bool Direction);


void displayAngle(float angle , bool Direction);

void Display_Direction ();

unsigned int readLCDButtons();


void setup() {
    Serial.begin(115200);

    // Set up stepper motor pins
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(ENABLE_PIN, OUTPUT);

    // Enable the stepper driver
    digitalWrite(ENABLE_PIN, LOW); // LOW to enable

    // Initialize LCD
    lcd.begin(16, 2);
    lcd.cursor(); // Show cursor
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" CONTROL TYPE");
    lcd.setCursor(0, 1);
    lcd.print("> SPEED  ");
    lcd.print("  ANGLE ");
    Serial.println("Setup completed\n");
}

void loop() {

    int buttonState = readLCDButtons(); // Read button state
    if (buttonState != BUTTON_NULL) {
        if (selectedControl == MODE_SELECTION) {
            // Mode selection: toggle between SPEED and ANGLE
            if (buttonState == BUTTON_RIGHT || buttonState == BUTTON_LEFT) {
                Serial.println("Switch");
                Serial.println(CurrentSelection);
                lcd.setCursor(0, 1);
                CurrentSelection = !(CurrentSelection) ;
                if(CurrentSelection == MODE_SPEED){
                  lcd.print("> SPEED    ANGLE");
                }else{
                  lcd.print("  SPEED  > ANGLE");
                }
            } 
            else if (buttonState == BUTTON_SELECT) {
                if(CurrentSelection == MODE_SPEED) {
                    selectedControl = MODE_SPEED;
                } else{selectedControl = MODE_ANGLE;}
                lcd.clear();
                lcd.cursor();
                if (selectedControl == MODE_SPEED) {
                    lcd.setCursor(0, 0);
                    lcd.print("   Speed Mode");

//                    Display.displaySpeed(motorSpeed , rotationDir);
                } 
                else if (selectedControl == MODE_ANGLE) {
                    lcd.setCursor(0, 0);
                    lcd.print("   Angle Mode");
                    lcd.setCursor(0, 1);
                    lcd.print("Angle: ");
                    displayAngle(motorAngle, rotationDir );
                }
            }
        } 
        else if (selectedControl == MODE_SPEED) {
            handleSpeedMode(buttonState);
        } 
        else if (selectedControl == MODE_ANGLE) {
            handleAngleMode(buttonState);
        }
    }
}

// Helper functions
void handleSpeedMode(int buttonState) {
    // Handle speed adjustments and display logic
    if (buttonState == BUTTON_SELECT) {
        isLocked = !isLocked;
        lcd.setCursor(lcdCursorPos, 1);
        lcd.cursor();
    } else if (!isLocked) {
        adjustSpeed(buttonState);
    }
}

void handleAngleMode(int buttonState) {
    // Handle angle adjustments and display logic
    if (buttonState == BUTTON_SELECT) {
        isLocked = !isLocked;
        lcd.setCursor(lcdCursorPos, 1);
        lcd.cursor();
    } else if (!isLocked) {
        adjustAngle(buttonState);
    }
}








