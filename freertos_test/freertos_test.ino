#include <Arduino_FreeRTOS.h>


void setup() {
    
Blink_init();
Blink2_init();


  Serial.begin(115200);
  xTaskCreate(TaskBlink,"Blink",128,NULL,2,NULL);
  xTaskCreate(TaskBlink2,"Blink2",128,NULL,2,NULL);

  
}

void loop(){}





void Blink_init(){
  pinMode(LED_BUILTIN, OUTPUT);
  }


  
void TaskBlink(void * parameter)  
{ while(1){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS );// wait for one second
    Serial.println("i can run two functions at the same time");
}
}



void Blink2_init(){pinMode(12, OUTPUT);}



void TaskBlink2(void * parameter)  
{while(1){
    digitalWrite(12, LOW);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    Serial.println("i can run two functions at the same time$$$$$$$$$$$$");
    digitalWrite(12, HIGH);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
}}
