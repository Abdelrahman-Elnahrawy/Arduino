/*
Arduino 2x16 LCD - LCD Scroll
modified on 18 Feb 2019
by Saeed Hosseini
https://electropeak.com/learn/
*/
#include 
const int RS = 8;
const int EN = 9;
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;
const int pin_BL = 10; // arduino pin wired to LCD backlight circuit
LiquidCrystal lcd( RS,  EN,  d4,  d5,  d6,  d7);
void setup() {
 lcd.begin(16, 2);
 lcd.print("Electropeak");
 delay(1000);
}
void loop() {
 // scroll 11 positions ("Electropeak" length) to the left
 for (int positionCounter = 0; positionCounter < 11; positionCounter++) {
   lcd.scrollDisplayLeft();
   delay(400);  //Scrolling speed
 }
 // scroll 27 positions ("Electropeak" length + display length) to the right
 for (int positionCounter = 0; positionCounter < 27; positionCounter++) {
   lcd.scrollDisplayRight();
   delay(400);
 }
 // scroll 16 positions (display length) to the left
 for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
   lcd.scrollDisplayLeft();
   delay(50);
 }
 delay(1000);
} 