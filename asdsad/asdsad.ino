/**
 * Name: write_to_EEprom.ino
 * Version: 1.0
 * Creation Date:12/11/2017
 * Author: Ab Kurk
 * Description:
 * This sketch is part of a tutorial to teach you how to create a user configurable IOT project
 * using the ESP8266 Adafruit HUzzah. This sketch simply converts a float value into a string 
 * and then writes this string to the flash memory using the EEPROM library
 */

#include <EEPROM.h> //The EEPROM libray 
String PASSS;
String eeprom;
char* USR="Na7rawy Limited";
char* PASS="Selim&Nahrawy751";

void setup() {
eeprom=String(USR);
PASSS=String(PASS);
eeprom=eeprom+"$"+PASS+"$";
Serial.begin(115200);
//Setup EEPROM memory space
EEPROM.begin(512);

//For Loop for writing to flash memory
for(int n=0; n< eeprom.length();n++){
  EEPROM.write(n,eeprom[n]);
}
//finishing of writing procedures
EEPROM.commit();
}

void loop() {
for(int n=0; n< eeprom.length();n++){
  Serial.print((char)eeprom[n]);
}
Serial.println();
delay(550);
}
