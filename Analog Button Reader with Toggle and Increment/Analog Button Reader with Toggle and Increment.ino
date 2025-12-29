boolean R1     =0;
boolean R2     =0;
boolean R3     =0;
boolean R4     =0;
boolean R5     =0;
int R6     =0;
unsigned long button_time= 0;
void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned long now = millis();
  if(now - button_time > 1000){button_time = now;
if( analogRead(A0)>=0  && analogRead(A0)<100 ){R1=!R1;   
}
if( analogRead(A0)>200 && analogRead(A0)<300 ){R2=!R2;   
}
if(analogRead(A0)> 400 && analogRead(A0)<500 ){R3=!R3;  
}
if(analogRead(A0)> 600 && analogRead(A0)<700 ){R4=!R4;   
}
if(analogRead(A0)> 700 && analogRead(A0)<800 ){R5=!R5;  
}
if( analogRead(A0)>900 && analogRead(A0)<1020){R6=R6+10; 
}
Serial.println ( analogRead(A0)); 

        Serial.print (  "R1:"); Serial.print   (R1);
        Serial.print ("  R2:"); Serial.print   (R2);
        Serial.print ("  R3:"); Serial.print   (R3);
        Serial.print ("  R4:"); Serial.print   (R4);
        Serial.print ("  R5:"); Serial.print   (R5);
        Serial.print ("  R6:"); Serial.println (R6);
}


}
