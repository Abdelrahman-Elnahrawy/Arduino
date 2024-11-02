// initializes or defines the output pin of the LM35 temperature sensor
int outputpin= A0;
//this sets the ground pin to LOW and the input voltage pin to high
void setup() {
Serial.begin(9600); 
}

void loop()       //main loop

{
int analogValue = analogRead(outputpin);
float celsius = analogValue/10;
Serial.print("in DegreeC=   ");
Serial.println(celsius);


Serial.println(analogValue);
delay(200);
}
