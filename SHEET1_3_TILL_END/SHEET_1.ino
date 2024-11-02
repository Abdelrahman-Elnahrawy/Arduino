/**************************************************************
 *Introduction to Embeded systems *****ASU COURSE**************
 * 888888888888888888888---SHEET_1---88888888888888888888888888
 * TO COMBILE THE CODE OR PLAY WITH IT UN COMMENT THE SECTION**
 * NEEDED ************THANK U <3 <<<<>>>>>><<<<<<>>>>>><<<<>>>>
 *************************************************************/






 /*************************************************************
 * 888888888888888888888---SHEET_1-1-88888888888888888888888888
 *****************************IDIOT_PWM***********************/


 
/**************************************************************
int x = 2000*25/100;
void setup() {
pinMode(7,OUTPUT);


}

void loop() {
 digitalWrite(7,HIGH);
 delay(500);
 digitalWrite(7,LOW);
 delay(1500);
}
**************************************************************/


 /*************************************************************
 * 888888888888888888888---SHEET_1-2-88888888888888888888888888
 *****************************BOUNCING LEDS*******************/

 
/**************************************************************


int LEDS[4] = {4,5,6,7} ;
void setup() {
for (int i=0;i<4;i++){
  pinMode(LEDS[i],OUTPUT);
}

}

void loop() {
for(int i=0;i<4;i++){
  digitalWrite(LEDS[i],HIGH);
  delay(500);
  digitalWrite(LEDS[i],LOW);
 }
 digitalWrite(7,HIGH);
 for(int i=3;i>0;i--){
digitalWrite(LEDS[i],HIGH);
  delay(500);
  digitalWrite(LEDS[i],LOW);
  }
}
**************************************************************/


 /*************************************************************
 * 888888888888888888888---SHEET_1-3-88888888888888888888888888
 *****************************Prime_numbers*******************/

 
/**************************************************************
int number = 0;
int x = 2;     /// the prime number number
void setup() {
Serial.begin(9600);
Serial.println( "the prime number is : 2");
Serial.println( "the prime number is : 3");
}

void loop() {
  if (x <1000){                 // the maximuim  prime number tested
 number ++ ;
for (int i = 2 ; i<(number/2) ; i++){ // number loop start from 2  till it reaches number tested
if (number%i==0){  /// if the number tested is divisable by any number less than it without a reminder remaining the loops break and begin again from the next number
break;
}
if (i == (number/2) -1){
Serial.print( "the prime number is : "); // when the number reaches the end of the loob without break // therfore this is a prime number
Serial.println ( number , DEC);
x++;
}
}
  }
  }

  

***************************************************************/

 /*************************************************************
 * 888888888888888888888---SHEET_1-4-8888888888888888888888888
 ************************PWM_SERIAL-INACCURATE****************/

/**************************************************************

 
unsigned long D,N,X;
int incomingByte = 0;
void setup (){
  pinMode(13,1);
  Serial.begin(9600);
 

  } 
  void loop (){
          if (Serial.available() > 0) {
                incomingByte = Serial.read();
  X=0;        
if (incomingByte == 68){
D=0;
   Serial.println("waiting for delay entry .. plese enter the value... THEN PRESS ENTER");
    Serial.println(); Serial.println();
while (1){
     //Serial.println("in the while");
  if (Serial.available() > 0){
    incomingByte = Serial.read();
    if( incomingByte == 13 ){
         Serial.println("delay saved");
      break;
      }
      if (incomingByte >47  && incomingByte <58){
        
        D = D *pow(10,X)+(incomingByte-48);
          X++;
        if (X>1){
          X=1;
          }
 
    Serial.print("D = ");
    Serial.print(D);
    Serial.println("            to finish.....PRESS ENTER");
     Serial.println();
      }
    }
    
  
  }
}

if (incomingByte == 78){
    N=0;

   Serial.println("waiting for No. of pulses entry ..plese enter the value.. THEN PRESS ENTER");
    Serial.println();
     Serial.println();
while (1){
     //Serial.println("in the while");
  if (Serial.available() > 0){
    incomingByte = Serial.read();
    if( incomingByte == 13 ){
         Serial.println("No. saved");
      break;
      }
      if (incomingByte >47  && incomingByte <58){
        
        N = N *pow(10,X)+(incomingByte-48);
          X++;
        if (X>1){
          X=1;
          }
 
    Serial.print("N = ");
    Serial.print(N);
    Serial.println("                  to finish.....PRESS ENTER");
      }
    }
    
  
  }
}



    if (incomingByte == 83){ 
       Serial.println("LOOB started");
        Serial.println();   
 for (int i=0 ; i < N ; i++){
      digitalWrite(13, 1);
      delay (D/2);
      digitalWrite(13, 0);
      delay(D/2);
    }
    Serial.println("DONE ");
    Serial.println();
    }

    
Serial.println("FOR delay value change press            D ");
 Serial.println();
Serial.println("FOR No. of pulses value change press    N ");
 Serial.println();
Serial.println("to start the loop press                 S ");
 Serial.println();
    Serial.print("N = ");
    Serial.print(N);
    Serial.print("------ D = ");
    Serial.println(D);
      Serial.println();
        


      }
      }
****************************************************************************************************/



 /***************************************************************************************************
 * 88888888888888888888888888888888888888888---SHEET_1-6-88888888888888888888888888888888888888888888
 * **************************************************************************************************
 * Write embedded program that calculate the square root of any given float value. The program should
receive the values using serial communication. Also, write the computer program that sends this value
and then prints the output.**************************************************************************
 **************************************************************MAM_INPUT_4 DIGITS*******************/




/****************************************************************************************************
float x,s ;
int y,income  ;
int z=0  ;
void setup(){
 Serial.begin(9600);
   Serial.println ("welcome to dumb root");
  Serial.println ("____________________________");
   Serial.println ("FOR ANSWER PRESS ENTER");
  Serial.println ("please enter a integer input NUMBER OR (.)");
}
void loop (){
if(Serial.available()>0){
  income = Serial.read();
        if (income >47  && income <58){
        x = x *pow(10,y)+(income-48);
          y++;
        if (y>1){y=1;} 
        Serial.print("THE NUMBER:  ");
        Serial.println(x,0);  
           
}
else if (income==46){
      Serial.print("THE NUMBER:  ");
      Serial.print(x,0); 
      Serial.println(".");
  while(1){
    if(Serial.available()>0){
        income = Serial.read();
      if (income==13){
        s = pow (x,0.5);
 Serial.print("THE ANSWER IS:    ");
Serial.println(s,8);
s=0;
x=0;
y=0;
z=0;
      break;
    }
    if (income >47  && income <58){
        z--;
x = x + (income-48)*pow(10,z);
        Serial.print("THE NUMBER:  ");
        Serial.println(x,4);  
    }
    }
  }
}
  else if (income==13){
s = pow (x,0.5);
  Serial.print("THE ANSWER IS:    ");
Serial.println(s,8);
s=0;
x=0;
y=0;
z=0;
  }
else{
  Serial.println ("FOR ANSWER PRESS ENTER");
  Serial.println ("please enter a valid input NUMBER OR (.)");
  Serial.println (income);
  }

}

}


****************************************************************************************************/


/************************************************************************************
888888888888888888888888888888888---the easy dumb way-----888888888888888888888888888
*/
/**********************************************************************************
void setup()
{
Serial.begin(9600);
Serial.print("*******enter the data quickly**********");
Serial.print("wait about a 3 seconds to get an output");
Serial.print("because umm arduino stuff T_T");

}

void loop()
{
if(Serial.available()>0)
{
float i = Serial.parseFloat( );
Serial.print("your data is: ");
Serial.println( i,8);
Serial.print("The Square root is: ");
Serial.println(sqrt(i),DEC);
}

}
****************************************************************************************************/

 /***************************************************************************************************
 * 88888888888888888888888888888888888888888---SHEET_1-7-88888888888888888888888888888888888888888888
 * **************************************************************************************************
 * Write embedded program that takes following text commands and produce the appropriate result.*****
“sum 7.63 2.76 4.7 8.2 3.4 6.7 5.4 3.2\n”************************************************************
“mul 7.63 2.76 4.7 8.2 3.4 6.7 5.4 3.2\n”************************************************************
“average 7.63 2.76 4.7 8.2 3.4 6.7 5.4 3.2\n”********************************************************
 **************************************************************calculator***************************/

/****************************************************************************************************

#define     sum 0
#define     mul 1
#define average 2
int state;
float x,s ;
int y,income,n  ;  
int z=0  ;
void decorate(){
   Serial.println  ("____________________________________________________");
 Serial.println  ("###################input examples###################");
  Serial.println("sum     7.63 2.76 4.7 8.2 3.4 6.7 5.4 3.2\n");
 Serial.println ("mul     7.63 2.76 4.7 8.2 3.4 6.7 5.4 3.2\n");
 Serial.println ("average 7.63 2.76 4.7 8.2 3.4 6.7 5.4 3.2\n");
  Serial.println  ("--s for sum -- sbace for step---\ for result--------");
  Serial.println  ("####################################################");
  Serial.println  ("____________________________________________________");
}
void get_input(){
while(1){
if (Serial.available()>0){
  income = Serial.read();
     if (income==32){
                  z=0;
                  y=0;
                  switch (state){
                  case mul:
                  s = s*x;
                  break;
                  case sum : s=s+x ;
                  break;
                  case average : s=s+x ;
                  n++;
                  break;}
                  x =0 ;
                      Serial.print("reuslt:  ");
                      Serial.println(s,3);
                 
                  }
  if (income > 47  && income <58){
    x = x*pow(10,y) + (income-48);
    y++;
    if (y>1){y=1;}
    Serial.print("the value entered:  ");
    Serial.println(x,0);
    }
  else if (income==46){  
          Serial.print("the value entered:  ");
          Serial.print(x,0); 
          Serial.println(".");
               while(1){
                if(Serial.available()>0){
                  income = Serial.read();
                  if (income >47  && income <58){
                      z--;
                      x = x + (income-48)*pow(10,z);
                      Serial.print("the value entered:  ");
                      Serial.println(x,2); }
                 if (income==32){
                  z=0;
                  y=0;
                  switch (state){
                  case mul:
                  s = s*x;
                  break;
                  case sum : s=s+x ;
                  break;
                  case average : s=s+x ;
                  n++;
                  break;}
                  x =0 ;
                      Serial.print("reuslt:  ");
                      Serial.println(s,3);
                  break;
                  }

                          }
                    }
      
      
          }
   if (income==92){
                      switch (state){
                  case mul:
                    Serial.print("multiplication result:  ");
                   Serial.println(s,5);
                  break;
                  case sum :
                     Serial.print("summation result:  ");
                      Serial.println(s,5);
                  break;
                  case average :
                     Serial.print("average result:  ");
                      Serial.println((s/(n)),5);
                      n=0;
                  break;}
    
    
    Serial.println("thank u");
    x=0;
    y=0;
    z=0;
    s=0;
    n=0;
    
     Serial.println ();
     Serial.println ();
     Serial.println ();
     Serial.println ();
decorate();
 break;}
  }
}
}

void setup(){
 Serial.begin(9600);

  
  Serial.println ("welcome to dumb calculator");
decorate();
}

void loop (){

 
if(Serial.available()>0){
  income = Serial.read();
if (income ==115){
 Serial.println ("SELECTED MODE IS ");
 Serial.println ("sum");
  state  =sum;
  get_input();

  
}
 else if (income ==109){
 Serial.println ("SELECTED MODE IS ");
 Serial.println ("multiplication");
 s=1;
 
  state = mul;
  get_input();

} 
else if (income ==97){
 Serial.println ("SELECTED MODE IS ");
 Serial.println ("average");
  state= average; 
  get_input();

}
}

}
****************************************************************************************************/


/*########################################################################################################################################################################################
thank u <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <3 <33 <3 <3 <3 <3 <3 <3 <3 <3 <3
/########################################################################################################################################################################################*/
