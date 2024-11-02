//GAS sensor output pin to Arduino analog A0 pin
#define R 2
#define G 7
#define B 5

#define MQ2 A0

int gaslevel;

void setup()
{
Serial.begin(9600); //Initialize serial port - 9600 bps

pinMode(MQ2,INPUT);
pinMode(R,OUTPUT);
pinMode(G,OUTPUT);
pinMode(B,OUTPUT);
}

void loop()
{
  gaslevel=(analogRead(MQ2));
  gaslevel=map(gaslevel,0,1023,0,255);
  
 if(gaslevel > 20 && gaslevel <= 30){//gaslevel is greater than 20 and less than 30
    digitalWrite(R,LOW);//green led is off
    digitalWrite(B,LOW);//blue led is off
     _delay_ms(500);//delay
    digitalWrite(G,HIGH);//red led is on
  _delay_ms(500);
  }
  else if(gaslevel > 30 && gaslevel <= 60){//gaslevel is greater than 30 and less than 60
        digitalWrite(R,LOW);//red led is off
         digitalWrite(G,LOW);//green led is off
         _delay_ms(500);
    digitalWrite(B,HIGH);//blue led is on
    
      }
      
       else if(gaslevel > 60 && gaslevel <= 90 ){//gaslevel is greater than 60 and less than 90
        digitalWrite(G,LOW);//red led is off
        digitalWrite(B,LOW);//blue led is off
         _delay_ms(500);
    digitalWrite(R,HIGH);//green led is on
      }
      else
      {
         digitalWrite(G,LOW);//red led is off
        digitalWrite(B,LOW);//blue led is off
    digitalWrite(R,LOW);//green led is off
      }
  Serial.println(gaslevel);//print values on serial monitor
delay(500);
}
