#include <LiquidCrystal.h>

/* --- CONFIGURATION --- */
#define SCREEN_SELECT        2
#define SCREEN_SPEED         1
#define SCREEN_ANGLE         0
#define MODE_SELECT          2

#define BUTTON_NULL          0
#define BUTTON_RIGHT         1
#define BUTTON_UP            2
#define BUTTON_DOWN          3
#define BUTTON_LEFT          4
#define BUTTON_SELECT        5
#define BUTTON_SELECT_HOLD   6

#define UPDATE_ALL_SCREEN    10
#define CLOCKWISE            0
#define MAX_SPEED            1000.0

/* --- HARDWARE --- */
// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

/* --- STATE VARIABLES --- */
char CurrentScreen   = MODE_SELECT;
bool selectedControl = 1;
float Angle          = 0;
float Speed          = 0;
bool RotationDirection = 0;
int CursorPosition   = 7;
bool LockScreen      = 1;

/* --- FUNCTION PROTOTYPES --- */
void DisplayUpdate(char command);
void DisplaySpeedScreen(char command);
void DisplayAngleScreen(char command);
void DisplaySelectionScreen(char command);
void DisplayCursorPositionUpdate(char command);
void DisplayChangeSpeed(char command);
void DisplayChangeAngle(char command);
void DisplayDirection(bool Direction);
void DisplayLockUpdate();
unsigned int readLCDButtons();

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.clear();

  // --- STARTUP DEMO ---
  lcd.setCursor(2, 0);
  lcd.print("HELLO USER!");
  lcd.setCursor(0, 1);
  lcd.print("LCD SYSTEM READY");
  delay(2000);
  
  lcd.clear();
  DisplayUpdate(UPDATE_ALL_SCREEN);
  Serial.println("Setup completed");
}

void loop() {
  unsigned int button = readLCDButtons();
  
  if (button != BUTTON_NULL) {
    DisplayUpdate(button);
  }
}

/* --- GUI LOGIC --- */

unsigned int readLCDButtons() {
  int adcKeyIn = analogRead(0);
  int button = BUTTON_NULL;

  if (adcKeyIn < 1000) {
    delay(100); // Debounce
    adcKeyIn = analogRead(0);

    if (adcKeyIn < 50)        button = BUTTON_RIGHT;
    else if (adcKeyIn < 200)  button = BUTTON_UP;
    else if (adcKeyIn < 380)  button = BUTTON_DOWN;
    else if (adcKeyIn < 600)  button = BUTTON_LEFT;
    else if (adcKeyIn < 850)  button = BUTTON_SELECT;

    int counter = 0;
    while (analogRead(0) < 1000) {
      counter++;
      delay(100);
      if (button == BUTTON_SELECT && counter > 20) {
        CurrentScreen = SCREEN_SELECT;
        button = BUTTON_SELECT_HOLD;
        lcd.noCursor();
        LockScreen = 1;
        DisplayUpdate(BUTTON_SELECT_HOLD);
      }
    }
  }
  return button;
}

void DisplayUpdate(char command) {
  if (command == BUTTON_SELECT) {
    switch (CurrentScreen) {
      case SCREEN_SPEED:
      case SCREEN_ANGLE:
        DisplayLockUpdate();
        break;
      default:
        if (selectedControl == SCREEN_SPEED) {
          CurrentScreen = SCREEN_SPEED;
          DisplaySpeedScreen(UPDATE_ALL_SCREEN);
        } else {
          CurrentScreen = SCREEN_ANGLE;
          DisplayAngleScreen(UPDATE_ALL_SCREEN);
        }
        DisplayLockUpdate();
        break;
    }
  } else {
    switch (CurrentScreen) {
      case SCREEN_SPEED: DisplaySpeedScreen(command); break;
      case SCREEN_ANGLE: DisplayAngleScreen(command); break;
      default:           DisplaySelectionScreen(command); break;
    }
  }

  if (CurrentScreen != SCREEN_SELECT) {
    DisplayDirection(RotationDirection);
  }
}

void DisplaySpeedScreen(char command) {
  if (command == UPDATE_ALL_SCREEN) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   Speed Mode");
    lcd.setCursor(0, 1);
    lcd.print("Speed: ");
  }
  DisplayCursorPositionUpdate(command);
  DisplayChangeSpeed(command);
  
  int speedInteger = (int)Speed;
  lcd.setCursor(6, 1);
  lcd.print(speedInteger > 999 ? speedInteger / 1000 : 0);
  lcd.print((speedInteger % 1000) / 100);
  lcd.print((speedInteger % 100) / 10);
  lcd.print(speedInteger % 10);
  lcd.print(".");
  lcd.print((int)((Speed - floorf(Speed)) * 10));
  lcd.setCursor(CursorPosition, 1);
}

void DisplayAngleScreen(char command) {
  if (command == UPDATE_ALL_SCREEN) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   Angle Mode");
    lcd.setCursor(0, 1);
    lcd.print("Angle:  ");
  }
  DisplayCursorPositionUpdate(command);
  DisplayChangeAngle(command);
  
  int angle_Integer = (int)Angle;
  lcd.setCursor(7, 1);
  lcd.print((angle_Integer % 1000) / 100);
  lcd.print((angle_Integer % 100) / 10);
  lcd.print(angle_Integer % 10);
  lcd.print(".");
  lcd.print((int)((Angle - floorf(Angle)) * 10));
  lcd.setCursor(CursorPosition, 1);
}

void DisplaySelectionScreen(char command) {
  if (command == UPDATE_ALL_SCREEN) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" CONTROL TYPE");
  }
  if (command == BUTTON_RIGHT || command == BUTTON_LEFT) {
    selectedControl = (selectedControl == SCREEN_SPEED) ? SCREEN_ANGLE : SCREEN_SPEED;
  }
  lcd.setCursor(0, 1);
  lcd.print((selectedControl == SCREEN_SPEED) ? "> SPEED    ANGLE " : "  SPEED  > ANGLE ");
}

void DisplayCursorPositionUpdate(char command) {
  int MinCursorPosition = (CurrentScreen == SCREEN_SPEED) ? 6 : 7;
  if (command == BUTTON_LEFT) {
    CursorPosition--;
    if (CursorPosition == 10 || CursorPosition == 12) CursorPosition--;
    if (CursorPosition < MinCursorPosition) CursorPosition = 13;
  } else if (command == BUTTON_RIGHT) {
    CursorPosition++;
    if (CursorPosition == 10 || CursorPosition == 12) CursorPosition++;
    if (CursorPosition > 13) CursorPosition = MinCursorPosition;
  }
  
  lcd.setCursor(13, 1);
  if (CursorPosition == 13) {
    lcd.print(">");
    lcd.noCursor();
  } else {
    lcd.print(" ");
    if(!LockScreen) lcd.cursor();
  }
  lcd.setCursor(CursorPosition, 1);
}

void DisplayChangeSpeed(char command) {
  if (command == BUTTON_UP || command == BUTTON_DOWN) {
    float change = 0;
    if (CursorPosition == 6) change = 1000;
    else if (CursorPosition == 7) change = 100;
    else if (CursorPosition == 8) change = 10;
    else if (CursorPosition == 9) change = 1;
    else if (CursorPosition == 11) change = 0.1;
    else if (CursorPosition == 13) {
      RotationDirection = !RotationDirection;
      return;
    }
    
    if (command == BUTTON_UP) Speed += change;
    else Speed -= change;

    if (Speed > MAX_SPEED) Speed = MAX_SPEED;
    if (Speed < 0) Speed = 0;
  }
}

void DisplayChangeAngle(char command) {
  if (command == BUTTON_UP || command == BUTTON_DOWN) {
    float change = 0;
    if (CursorPosition == 7) change = 100;
    else if (CursorPosition == 8) change = 10;
    else if (CursorPosition == 9) change = 1;
    else if (CursorPosition == 11) change = 0.1;
    else if (CursorPosition == 13) {
      RotationDirection = !RotationDirection;
      return;
    }

    if (command == BUTTON_UP) Angle += change;
    else Angle -= change;

    if (Angle >= 360) Angle -= 360;
    if (Angle < 0) Angle += 360;
  }
}

void DisplayDirection(bool Direction) {
  lcd.setCursor(14, 1);
  lcd.print(Direction == CLOCKWISE ? "CW" : "CC");
  lcd.setCursor(CursorPosition, 1);
}

void DisplayLockUpdate() {
  if (LockScreen) { LockScreen = 0; lcd.cursor(); }
  else            { LockScreen = 1; lcd.noCursor(); }
}