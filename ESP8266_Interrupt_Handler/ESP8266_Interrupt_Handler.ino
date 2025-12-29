




uint8_t Switch_1 = 5; //D1
uint8_t Switch_2 = 4; //D2
uint8_t Switch_3 = 0; //D3

uint8_t Button_1 = 12; //D6
uint8_t Button_2 = 13; //D7
uint8_t Button_3 = 14; //D5

bool R1 ;
bool R2 ;
bool R3 ;
unsigned long last_trigger;
#define TRIGGER_DELAY 700
void Update_Switchs(){
  digitalWrite(Switch_1,R1);
  digitalWrite(Switch_2,R2);
  digitalWrite(Switch_3,R3);
  }
void setup() {
  Serial.begin(115200);
  
  pinMode(Switch_1,OUTPUT);
  pinMode(Switch_2,OUTPUT);
  pinMode(Switch_3,OUTPUT);

  pinMode(Button_1,INPUT_PULLUP);
  pinMode(Button_2,INPUT_PULLUP);
  pinMode(Button_3,INPUT_PULLUP);

 attachInterrupt(digitalPinToInterrupt(Button_1), IntCallback_R1, RISING);
 attachInterrupt(digitalPinToInterrupt(Button_2), IntCallback_R2, RISING);
 attachInterrupt(digitalPinToInterrupt(Button_3), IntCallback_R3, RISING);
}


void loop() {
  Update_Switchs();
}


IRAM_ATTR  void IntCallback_R1(){
  
  if(millis()-last_trigger>TRIGGER_DELAY){
    Serial.println("switching 1");
    last_trigger = millis();
  R1=!R1;}}
  
IRAM_ATTR  void IntCallback_R2(){
    if(millis()-last_trigger>TRIGGER_DELAY){
       Serial.println("switching 2");
    last_trigger = millis();
  R2=!R2;}}
IRAM_ATTR  void IntCallback_R3(){
    if(millis()-last_trigger>TRIGGER_DELAY){
       Serial.println("switching 3");
    last_trigger = millis();
  R3=!R3;}}
