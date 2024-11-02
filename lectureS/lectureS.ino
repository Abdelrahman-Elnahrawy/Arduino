#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 13, 7,6,5,4); // sets the interfacing pins

#define TEMP_OUT <PIN1> // output from the temperature sensor to the arduino board
#define BUTTON <PIN2> // the push button to switch between min and max temp modes
#define FAN <PIN3> // output from the arduino board to the fan 
#define FAN_LED <PIN4> // output from the arduino board to the fan led 
#define ALARM_LED <PIN5> // output from the arduino board to the alarm led 

// screen modes
#define CURRENT_TEMP 0
#define MIN_TEMP 1
#define MAX_TEMP 2

#define LIMIT 30000

unsigned long lastTime = millis();
float minTemp = getTemp();
float maxTemp = getTemp();

int screenMode = CURRENT_TEMP;

float getTemp()
{
  float curr_temp = <line1>;
  return curr_temp;
}

void setup() {
  interrupts();
  lcd.begin(16, 2);
  pinMode(FAN,OUTPUT);
  pinMode(FAN_LED,OUTPUT);
  pinMode(ALARM_LED,OUTPUT);
  pinMode(BUTTON,<MODE1>);
  attachInterrupt(0,<function_name>,FALLING);
  showCurrentTemp();
}
void showCurrentTemp()
{
  lcd.setCursor(0,0);
  lcd.print("Temp : ");
  lcd.print(getTemp(),DEC);
}
void showMinTemp()
{
  lcd.setCursor(0,0);
  lcd.print("Min Temp : ");
  lcd.print(minTemp,DEC);
}
void showMaxTemp()
{
  lcd.setCursor(0,0);
  lcd.print("Min Temp : ");
  lcd.print(maxTemp,DEC);
}
void changeState()
{
  lastTime = millis();
  if(screenMode==CURRENT_TEMP)
  {
  screenMode = <MODE2>;
  <function1>;
  }
  if(screenMode==MIN_TEMP)
  {
  screenMode = <MODE3>;
  <function2>;
  }
  if(screenMode==MAX_TEMP)
  {
  screenMode = <MODE4>;
  <function3>;
  }
}
void loop() {
  float currTemp = getTemp();
  if(<C1>)
  minTemp = currTemp;
  if(<C2>)
  maxTemp = currTemp;
  if(<C3>)
  showCurrentTemp();
  if(<C4>)
  {
  analogWrite(FAN,0);
  digitalWrite(FAN_LED,LOW);
  digitalWrite(ALARM_LED,LOW);
  }
  else if(<C5>)
  {
  analogWrite(FAN,map(currTemp,0,1023,0,255));
  digitalWrite(FAN_LED,HIGH);
  digitalWrite(ALARM_LED,LOW);
  }
  else if(<C6>)
  {
  analogWrite(FAN,0);
  digitalWrite(FAN_LED,LOW);
  digitalWrite(ALARM_LED,HIGH);
  }
}
