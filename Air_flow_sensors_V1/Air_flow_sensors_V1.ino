int ERORR;
float CurrentReadingO;
float SumO;
float AverageO;
float MeasuresNO=10 ; // number of measures to average
float OF;
float CurrentReadingA;
float SumA;
float AverageA;
float MeasuresNA=10 ;
float AF;
float CurrentReadingP;
float SumP;
float AverageP;
float MeasuresNP=10 ;
float IF;
// Patient air flow
float OFSUM;
// Oxygen flow summation over 3 sec
float AFSUM;
// Air flow summation over 3 sec
float IFSUM;
// Patient flow summation over 3 sec
unsigned long previousMillis1 = 0;
void setup() 
{
Serial.begin(9600);
}

void loop() 
{unsigned long currentMillis1 = millis();
for (int i=0; i<MeasuresNO; i++)
{
CurrentReadingO = analogRead(A5);
SumO+=CurrentReadingO;
delay(1);
}
for (int i=0; i<MeasuresNA; i++)
{
CurrentReadingA = analogRead(A6);
SumA+=CurrentReadingA;
delay(1);
}
for (int i=0; i<MeasuresNA; i++)
{
CurrentReadingA = analogRead(A6);
SumA+=CurrentReadingA;
delay(1);
}
for (int i=0; i<MeasuresNP; i++)
{
CurrentReadingP = analogRead(A6);
SumP+=CurrentReadingP;
delay(1);
AverageO=SumO/MeasuresNO;
SumO=0;
AverageA=SumA/MeasuresNA;
SumA=0;
AverageP=SumP/MeasuresNP;
SumP=0;
}

AverageO=SumO/MeasuresNO;
SumO=0;
AverageA=SumA/MeasuresNA;
SumA=0;
AverageP=SumP/MeasuresNP;
SumP=0;
OFSUM=OFSUM+AverageO;
AFSUM=AFSUM+AverageA; 
IFSUM=IFSUM+AverageP;
if (currentMillis1 - previousMillis1 >=3000) {
if (IFSUM < (AFSUM+OFSUM)*.95 || IFSUM > (AFSUM+OFSUM)*1.05){
  ERORR=1;}
OFSUM=0;
AFSUM=0; 
IFSUM=0;  
}

/* This equation is not tested
this equation is not valid
etnafis team is not responsible of any damage
I used this linear equation to test on fan I had access to*/
OF=(AverageO-68)*0.265+2.7;
AF=(AverageO-68)*0.265+2.7;   
IF=(AverageO-68)*0.265+2.7;
}
