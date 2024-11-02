#define fan 3
/****************************** 
by usnig lm35 temprature sensor
******************************/
int value = 0;
int temprature = 0; //lm35 temprature sensor analog pin
void setup() {
pinMode(fan,OUTPUT);

}

void loop() {
value = analogRead(temprature);
float temp_in_celsius = ((value/1024)*5000)/10 ;

if (temp_in_celsius <20)
digitalWrite(fan,LOW);
else if (temp_in_celsius >40)
digitalWrite(fan,LOW);
else 
analogWrite(fan,(((temp_in_celsius - 20)*255)/20));    //the ratio of increse for example 23-20 =3, * 255 = 38 , for 40  the value will be 255 etc
}
