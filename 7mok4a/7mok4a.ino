#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


#define TIMER_INTERRUPT_DEBUG         1
#define _TIMERINTERRUPT_LOGLEVEL_     1

// Select a Timer Clock
#define USING_TIM_DIV1                false           // for shortest and most accurate timer
#define USING_TIM_DIV16               false           // for medium time and medium accurate timer
#define USING_TIM_DIV256              true            // for longest timer but least accurate. Default

#include <ESP8266TimerInterrupt.h>
ESP8266Timer ITimer;
ESP8266WebServer server;

const unsigned long interval = 1000; // 1 second interval
volatile bool timerFlag = false;

void handleTimerInterrupt() {
  timerFlag = true;
}

void setup() {
  // Initialize WiFi and server configuration
  // ...

  server.begin();

  // Set up the timer interrupt
ITimer.attachInterruptInterval( 500, handleTimerInterrupt);
}

void loop() {
  // Check if the timer interrupt flag is set
  if (timerFlag) {
    timerFlag = false; // Reset the flag

    // Handle client requests
    server.handleClient();

    // Perform other periodic tasks if needed
    // ...
  }

  // Other code and tasks can be executed here
  // ...
}
