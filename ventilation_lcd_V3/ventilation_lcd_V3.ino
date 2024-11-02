

#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//v0= pot, ledA = pot, rw&vss=gnd, vdd=+5v
int MP=15;
char *myStrings[] = {"Pressure A","Pressure","volume A","volume"};
char *myStrings1[] = {"1:1","1:2","1:3"};
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int mode = 2;
int oxygen = 21;
int rate = 15;
int ratio = 1;
int volume = 500;
void setup() {
  lcd.begin(16, 4);
  lcd.print("pressure:  cm.HOO2%:  % rate:   AAAAAAAAmode:           V:    ml I/E:   ");
  // the AAAAAAAA part is a dead part that doesnt appear on the screen
}
void loop() {
  if (ERORR){
    if (ERORR=1){lcd.setCursor(0,0);
      lcd.print("XXXXXXXXXXXXXXXXXXXXXXXXXXXXLECKAAAAAAAAAGEXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    }
  }
  else {
  lcd.setCursor(9,0);
  lcd.print(MP);
  lcd.setCursor(5,1);
  lcd.print(myStrings[mode]);
  lcd.setCursor(4,2);
  lcd.print(oxygen);
  lcd.setCursor(13,2);
  lcd.print(rate);
  lcd.setCursor(2,3);
  lcd.print(volume);
  lcd.setCursor(13,3);
  lcd.print(myStrings[ratio]);
  }
}
