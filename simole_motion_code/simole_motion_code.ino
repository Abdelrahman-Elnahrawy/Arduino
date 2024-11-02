

#include <Ps3Controller.h>

#include <Adafruit_NeoPixel.h>
#define BRIGHTNESS 50

#define neopixel  14
Adafruit_NeoPixel strip(30, neopixel, NEO_GRB + NEO_KHZ800);
int SPEED =9 ;
void initAhmed(){
  Serial.begin(9600);
  pinMode (neopixel , OUTPUT);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
  }

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void leds_blue() {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, strip.Color(  0,   0, 255));         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(50);                      //  Pause for a moment
  }
}


void specific(int pixels[]) {
  
  for(int i=0; i<strip.numPixels(); i++) { 
  for (int x=0; x<sizeof(pixels); x=x+1){
  if (pixels[x] == i){
      strip.setPixelColor(i, strip.Color(255,215,0));
      strip.show();   
      delay(10); 
    }
    }      //  Set pixel's color (in RAM)                       //  Update strip to match                           //  Pause for a moment
  }
}


void specific_clear(int pixels[]) {
  
  for(int i=0; i<strip.numPixels(); i++) { 
  for (int x=0; x<sizeof(pixels); x=x+1){
  if (pixels[x] == i){
      strip.setPixelColor(i, strip.Color(247, 0, 255));
      strip.show();    
      delay(10);
    }
    }      //  Set pixel's color (in RAM)                       //  Update strip to match                           //  Pause for a moment
  }
}


void show_speed() {
  
int s = ((SPEED*4)/9)+1;

    for(int i=0; i<5; i++) { 
      strip.setPixelColor(i+8, strip.Color(247, 0, 255));
      strip.show();  
    }
    
  for(int i=0; i<s; i++) { 
      strip.setPixelColor(i+8, strip.Color(64, 224, 208));
      strip.show();  
    } 
  }

/* MOTOR PINS  DEFINITION (.h) */



#define MOTOR1_1  4         //  ORANGE AT 4 TO PURPLE AT 19 YELLWOW AR 22 GREEN AT 23
#define MOTOR2_1  16        //
#define MOTOR1_2  17        //
#define MOTOR2_2  5         // 

#define MOTOR3_1  19        // 
#define MOTOR3_2  18        // 
#define MOTOR4_2  23        //
#define MOTOR4_1  22        //



/* IR reciver PINS  DEFINITION (.h) */

#define IR_FRONT_LEFT  34  // about  1200 on line  and 3400 without
int IR_FRONT_LEFT_PIXELS []= {20};
#define IR_FRONT_MID   35  // about  1500 on line  and 3440 without
int IR_FRONT_MID_PIXELS  []= {16,17};
#define IR_FRONT_RIGHT 32  // about  1200 on line  and 3700 without
int IR_FRONT_RIGHT_PIXELS[]= {13};

//above 3000 when no line // less than 2000 when have a line
#define IR_BACK_LEFT  25 // about  600 on line  and 2100 without
int IR_BACK_LEFT_PIXELS []= {0,1};
#define IR_BACK_MID   26 // about 1650 on line  and 3670 without
int IR_BACK_MID_PIXELS  []= {29};
#define IR_BACK_RIGHT 27 // about  900 on line  and 3200 without
int IR_BACK_RIGHT_PIXELS[]= {4};





// values for callibrating the sensors
const int IR_MOST_BLACK = 2000;
const int IR_LEAST_WHITE = 3000;


const int IR_FRONT_LEFT_T = 3530-500 ;
const int IR_FRONT_MID_T = 2760-500 ;
const int IR_FRONT_RIGHT_T = 2650-500 ;

const int IR_BACK_LEFT_T = 1450-500 ;
const int IR_BACK_MID_T = 3330-500 ;
const int IR_BACK_RIGHT_T = 2850-500 ;



// variables to save the sensors readings
int IR_FRONT_LEFT_READING = 0;
int IR_FRONT_MID_READING = 0;
int IR_FRONT_RIGHT_READING = 0;
int IR_BACK_LEFT_READING = 0;
int IR_BACK_MID_READING = 0;
int IR_BACK_RIGHT_READING = 0;




/*PWM DEFINTTIONS (.h)*/

#define MOTOR3_4_EN 15
#define MOTOR1_2_EN 13

#define PWMFreq        1000
#define RIGHT_MOTORS   1   //THE CHANNEL OF PWM
#define LEFT_MOTORS    0  //THE CHANNEL OF PWM
#define PWMResolution  6
#define factor 0.25
#define  F2 300

boolean Line_follower = 0 ;

const int MAX_DUTY_CYCLE = (int)(pow(2, PWMResolution) - 1); 

void forward(int duty) { // FOR STRAIGHT MOTION
  set_speed_left(duty );
  set_speed_right(duty);
  digitalWrite(MOTOR1_1, HIGH );
  digitalWrite(MOTOR1_2, LOW );
  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, LOW );
  digitalWrite(MOTOR3_1, HIGH);
  digitalWrite(MOTOR3_2, LOW );
  digitalWrite(MOTOR4_1, HIGH);
  digitalWrite(MOTOR4_2, LOW );
}


void reverse(int duty) { // FOR REVERSE MOTION
  set_speed_left(duty );
  set_speed_right(duty);
  digitalWrite(MOTOR1_1, LOW  );
  digitalWrite(MOTOR1_2, HIGH );
  digitalWrite(MOTOR2_1, LOW  );
  digitalWrite(MOTOR2_2, HIGH );
  digitalWrite(MOTOR3_1, LOW  );
  digitalWrite(MOTOR3_2, HIGH );
  digitalWrite(MOTOR4_1,  LOW );
  digitalWrite(MOTOR4_2,  HIGH );
}

void STOP() {
  digitalWrite(MOTOR1_1, HIGH);
  digitalWrite(MOTOR1_2, HIGH );
  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, HIGH);
  digitalWrite(MOTOR3_1, HIGH);
  digitalWrite(MOTOR3_2, HIGH);
  digitalWrite(MOTOR4_1, HIGH);
  digitalWrite(MOTOR4_2, HIGH);
}

void forward_right(int duty) { // FOR FORWARD-RIGHT MOTION
  set_speed_left(duty);
  set_speed_right(duty * factor);
  digitalWrite(MOTOR1_1, HIGH );
  digitalWrite(MOTOR1_2, LOW );
  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, LOW );
  digitalWrite(MOTOR3_1, HIGH);
  digitalWrite(MOTOR3_2, LOW );
  digitalWrite(MOTOR4_1, HIGH);
  digitalWrite(MOTOR4_2, LOW );
}
void forward_left(int duty) { // FOR FORWARD-LEFT MOTION
  set_speed_left(duty * factor);
  set_speed_right(duty);
  digitalWrite(MOTOR1_1, HIGH );
  digitalWrite(MOTOR1_2, LOW );
  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, LOW );
  digitalWrite(MOTOR3_1, HIGH);
  digitalWrite(MOTOR3_2, LOW );
  digitalWrite(MOTOR4_1, HIGH);
  digitalWrite(MOTOR4_2, LOW );
}
void reverse_right(int duty) { // FOR REVERSE-RIGHT MOTION
  set_speed_left(duty);
  set_speed_right(duty * factor);
  digitalWrite(MOTOR1_1, LOW  );
  digitalWrite(MOTOR1_2, HIGH );
  digitalWrite(MOTOR2_1, LOW  );
  digitalWrite(MOTOR2_2, HIGH );
  digitalWrite(MOTOR3_1, LOW  );
  digitalWrite(MOTOR3_2, HIGH );
  digitalWrite(MOTOR4_1,  LOW );
  digitalWrite(MOTOR4_2,  HIGH );
}
void reverse_left(int duty) { // FOR REVERSE-LEFT MOTION
  set_speed_left(duty * factor);
  set_speed_right(duty);
  digitalWrite(MOTOR1_1, LOW  );
  digitalWrite(MOTOR1_2, HIGH );
  digitalWrite(MOTOR2_1, LOW  );
  digitalWrite(MOTOR2_2, HIGH );
  digitalWrite(MOTOR3_1, LOW  );
  digitalWrite(MOTOR3_2, HIGH );
  digitalWrite(MOTOR4_1,  LOW );
  digitalWrite(MOTOR4_2,  HIGH );
}
void left(int duty) { // FOR LEFT MOTION
  set_speed_left(duty);
  set_speed_right(duty);
  digitalWrite(MOTOR1_1, HIGH  );
  digitalWrite(MOTOR1_2, LOW );
  digitalWrite(MOTOR2_1, HIGH  );
  digitalWrite(MOTOR2_2, LOW );
  digitalWrite(MOTOR3_1, LOW  );
  digitalWrite(MOTOR3_2, HIGH );
  digitalWrite(MOTOR4_1,  LOW );
  digitalWrite(MOTOR4_2,  HIGH );
}
 void right(int duty){ // FOR RIGHT MOTION
   set_speed_left(duty);
  set_speed_right(duty);
      digitalWrite(MOTOR1_1, LOW  );
      digitalWrite(MOTOR1_2, HIGH );
      digitalWrite(MOTOR2_1, LOW  );
      digitalWrite(MOTOR2_2, HIGH );
      digitalWrite(MOTOR3_1, HIGH  );
      digitalWrite(MOTOR3_2, LOW );
      digitalWrite(MOTOR4_1,  HIGH );
      digitalWrite(MOTOR4_2,  LOW );
 }




int player = 0;
int battery = 0;
unsigned long time_till_res = 0;
boolean restart =0;



void notify()
{
  //--- Digital cross/square/triangle/circle button events ---
  if ( Ps3.event.button_down.cross )
    Serial.println("Started pressing the cross button");
    
  if ( Ps3.event.button_up.cross ){
    Serial.println("Released the cross button");
    STOP();
  }

  if ( Ps3.event.button_down.square )
    Serial.println("Started pressing the square button");
     
  if ( Ps3.event.button_up.square ){
    Serial.println("Released the square button");
    STOP();
  }

  if ( Ps3.event.button_down.triangle )
    Serial.println("Started pressing the triangle button");
    
  if ( Ps3.event.button_up.triangle ){
    Serial.println("Released the triangle button");
    STOP();
  }

  if ( Ps3.event.button_down.circle )
    Serial.println("Started pressing the circle button");

  if ( Ps3.event.button_up.circle ){
    Serial.println("Released the circle button");
    STOP();
  }

  //--------------- Digital D-pad button events --------------
  if ( Ps3.event.button_down.up )
    Serial.println("Started pressing the up button");
  if ( Ps3.event.button_up.up ) {
    Serial.println("Released the up button");
    STOP();
  }/*FORWARD####FORWARD####FORWARD####FORWARD####FORWARD####FORWARD####FORWARD####FORWARD####FORWARD####FORWARD*/

  if ( Ps3.event.button_down.right )
    Serial.println("Started pressing the right button");
  if ( Ps3.event.button_up.right ) {
    Serial.println("Released the right button");
    STOP();
  }

  if ( Ps3.event.button_down.down )
    Serial.println("Started pressing the down button");
  if ( Ps3.event.button_up.down ) {
    Serial.println("Released the down button");
    STOP();
  }
  if ( Ps3.event.button_down.left )
    Serial.println("Started pressing the left button");
  if ( Ps3.event.button_up.left ){
    Serial.println("Released the left button");
    STOP();
  }

  //------------- Digital shoulder button events -------------
  if ( Ps3.event.button_down.l1 )
    Serial.println("Started pressing the left shoulder button");
  if ( Ps3.event.button_up.l1 )
    Serial.println("Released the left shoulder button");

  if ( Ps3.event.button_down.r1 )
    Serial.println("Started pressing the right shoulder button");
  if ( Ps3.event.button_up.r1 )
    Serial.println("Released the right shoulder button");

  //-------------- Digital trigger button events -------------
  if ( Ps3.event.button_down.l2 )
    Serial.println("Started pressing the left trigger button");
  if ( Ps3.event.button_up.l2 )
    Serial.println("Released the left trigger button");

  if ( Ps3.event.button_down.r2 )
    Serial.println("Started pressing the right trigger button");
  if ( Ps3.event.button_up.r2 )
    Serial.println("Released the right trigger button");

  //--------------- Digital stick button events --------------
  if ( Ps3.event.button_down.l3 )
    Serial.println("Started pressing the left stick button");
  if ( Ps3.event.button_up.l3 )
    Serial.println("Released the left stick button");

  if ( Ps3.event.button_down.r3 )
    Serial.println("Started pressing the right stick button");
  if ( Ps3.event.button_up.r3 )
    Serial.println("Released the right stick button");

  //---------- Digital select/start/ps button events ---------
  if ( Ps3.event.button_down.select )
    Serial.println("Started pressing the select button");
  if ( Ps3.event.button_up.select ){
    Serial.println("Released the select button");
    SPEED ++ ;
    if (SPEED >9)
    SPEED = 9;
    show_speed();
  }
  if ( Ps3.event.button_down.start )
    Serial.println("Started pressing the start button");
  if ( Ps3.event.button_up.start ){
    Serial.println("Released the start button");
      SPEED = SPEED -1 ;
    if (SPEED <1)
    SPEED = 1;
    show_speed();
  }
  if ( Ps3.event.button_down.ps )
    Serial.println("Started pressing the Playstation button");
  if ( Ps3.event.button_up.ps ){
    Serial.println("Released the Playstation button");
Line_follower = !Line_follower;
  }
  //---------------- Analog stick value events ---------------
  if ( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ) {
    Serial.print("Moved the left stick:");
    Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
    Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
    Serial.println();
  }

  if ( abs(Ps3.event.analog_changed.stick.rx) + abs(Ps3.event.analog_changed.stick.ry) > 2 ) {
    Serial.print("Moved the right stick:");
    Serial.print(" x="); Serial.print(Ps3.data.analog.stick.rx, DEC);
    Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ry, DEC);
    Serial.println();
  }

  //--------------- Analog D-pad button events ----------------
  if ( abs(Ps3.event.analog_changed.button.up) ) {
    Serial.print("Pressing the up button: ");
    Serial.println(Ps3.data.analog.button.up, DEC);
    if (Ps3.data.analog.button.up == 255)
    { /*##################################################################################################################*/
      forward(SPEED);
    }
  }

  if ( abs(Ps3.event.analog_changed.button.right) ) {
    Serial.print("Pressing the right button: ");
    Serial.println(Ps3.data.analog.button.right, DEC);
    if (Ps3.data.analog.button.right == 255) 
       {/*##################################################################################################################*/
       right(SPEED);
   }
  }

  if ( abs(Ps3.event.analog_changed.button.down) ) {
    Serial.print("Pressing the down button: ");
    Serial.println(Ps3.data.analog.button.down, DEC);
    if (Ps3.data.analog.button.down == 255) {/*##################################################################################################################*/
      reverse(SPEED);
    }
  }

  if ( abs(Ps3.event.analog_changed.button.left) ) {
    Serial.print("Pressing the left button: ");
    Serial.println(Ps3.data.analog.button.left, DEC);
    if (Ps3.data.analog.button.left == 255) {/*##################################################################################################################*/
      left(SPEED);
   }
  }

  //---------- Analog shoulder/trigger button events ----------
  if ( abs(Ps3.event.analog_changed.button.l1)) {
    Serial.print("Pressing the left shoulder button: ");
    Serial.println(Ps3.data.analog.button.l1, DEC);
  }

  if ( abs(Ps3.event.analog_changed.button.r1) ) {
    Serial.print("Pressing the right shoulder button: ");
    Serial.println(Ps3.data.analog.button.r1, DEC);
  }

  if ( abs(Ps3.event.analog_changed.button.l2) ) {
    Serial.print("Pressing the left trigger button: ");
    Serial.println(Ps3.data.analog.button.l2, DEC);
  }

  if ( abs(Ps3.event.analog_changed.button.r2) ) {
    Serial.print("Pressing the right trigger button: ");
    Serial.println(Ps3.data.analog.button.r2, DEC);
  }

  //---- Analog cross/square/triangle/circle button events ----
  if ( abs(Ps3.event.analog_changed.button.triangle)) {
    Serial.print("Pressing the triangle button: ");
    Serial.println(Ps3.data.analog.button.triangle, DEC);
    if (Ps3.data.analog.button.triangle == 255) 
       {/*##################################################################################################################*/
       forward_right(SPEED);
       }
  }

  if ( abs(Ps3.event.analog_changed.button.circle) ) {
    Serial.print("Pressing the circle button: ");
    Serial.println(Ps3.data.analog.button.circle, DEC);
    if (Ps3.data.analog.button.circle == 255) 
       {/*##################################################################################################################*/
       reverse_right(SPEED);
  }
  }

  if ( abs(Ps3.event.analog_changed.button.cross) ) {
    Serial.print("Pressing the cross button: ");
    Serial.println(Ps3.data.analog.button.cross, DEC);
    if (Ps3.data.analog.button.cross == 255) 
       {/*##################################################################################################################*/
       forward_left(SPEED);
      }
  }

  if ( abs(Ps3.event.analog_changed.button.square) ) {
    Serial.print("Pressing the square button: ");
    Serial.println(Ps3.data.analog.button.square, DEC);
    if (Ps3.data.analog.button.square == 255) 
       {/*##################################################################################################################*/
       reverse_left(SPEED);
       }
  }

  /*/---------------------- Battery events ---------------------
    if( battery != Ps3.data.status.battery ){
       battery = Ps3.data.status.battery;
       Serial.print("The controller battery is ");
       if( battery == ps3_status_battery_charging )      Serial.println("charging");
       else if( battery == ps3_status_battery_full )     Serial.println("FULL");
       else if( battery == ps3_status_battery_high )     Serial.println("HIGH");
       else if( battery == ps3_status_battery_low)       Serial.println("LOW");
       else if( battery == ps3_status_battery_dying )    Serial.println("DYING");
       else if( battery == ps3_status_battery_shutdown ) Serial.println("SHUTDOWN");
       else Serial.println("UNDEFINED");
    }*/

}


void onConnect(){
    Serial.println("Connected.");
    colorWipe(strip.Color(247, 0, 255), 50);
}















 
// TO TILT SLIGHTLY LEFT OR RIGHT U CAN CHANGE THE SPEED OF THE SIDE
void setup() {



    Serial.begin(115200);

    Ps3.attach(notify);
    Ps3.attachOnConnect(onConnect);
    Ps3.begin("00:1a:7d:da:71:10");
    Serial.println("Ready.");
    colorWipe(strip.Color(0, 0, 255), 50);


  
  /*  ledcSetup(PWMChannel, PWMFreq, PWMResolution); 
  this is a special cpmmand for esp32 as it has 
  built is pwm generator to reduce the computational laod 
  and the reserving interrupts
*/

  ledcSetup   (RIGHT_MOTORS, PWMFreq, PWMResolution);
  
  ledcAttachPin(MOTOR1_2_EN, RIGHT_MOTORS);
  
  ledcSetup   (LEFT_MOTORS, PWMFreq, PWMResolution);
  
  ledcAttachPin(MOTOR3_4_EN, LEFT_MOTORS);
  
  

    pinMode(MOTOR1_1, OUTPUT);
    pinMode(MOTOR2_1, OUTPUT);
    pinMode(MOTOR2_2, OUTPUT);
    
    pinMode(MOTOR3_1, OUTPUT);
    pinMode(MOTOR1_2, OUTPUT);
    pinMode(MOTOR3_2, OUTPUT);
    pinMode(MOTOR4_2, OUTPUT);
    pinMode(MOTOR4_1, OUTPUT);

      digitalWrite(MOTOR3_1, HIGH  );
      digitalWrite(MOTOR3_2, HIGH );
}


void loop() {

  
/*      if(!Ps3.isConnected())
        return;

        */

        
//Line_follower=1;



/*  
Serial.print(" IR_FRONT_LEFT_READING ");
Serial.println(IR_FRONT_LEFT_READING);
Serial.println("");
Serial.print(" IR_FRONT_MID_READING ");
Serial.println(IR_FRONT_MID_READING);
Serial.println("");
Serial.print(" IR_FRONT_RIGHT_READING ");
Serial.println(IR_FRONT_RIGHT_READING);
Serial.println("");
*/
Serial.println("");Serial.println("");Serial.println("");


Serial.print(" IR_BACK_LEFT_READING ");
Serial.println(IR_BACK_LEFT_READING);
Serial.println("");
Serial.print(" IR_BACK_MID_READING ");
Serial.println(IR_BACK_MID_READING);
Serial.println("");
Serial.print(" IR_BACK_RIGHT_READING ");
Serial.println(IR_BACK_RIGHT_READING);
Serial.println("");




delay(1000);
/*

if(IR_FRONT_LEFT_READING<IR_MOST_BLACK)
specific(IR_FRONT_LEFT_PIXELS);
if(IR_FRONT_MID_READING<IR_MOST_BLACK)
specific(IR_FRONT_MID_PIXELS);
if(IR_FRONT_RIGHT_READING<IR_MOST_BLACK)
specific(IR_FRONT_RIGHT_PIXELS);



//if(IR_BACK_LEFT_READING<IR_BACK_LEFT_T)
if(IR_BACK_LEFT_READING<1300)
specific(IR_BACK_LEFT_PIXELS);
if(IR_BACK_MID_READING<IR_BACK_MID_T)
specific(IR_BACK_MID_PIXELS);
if(IR_BACK_RIGHT_READING<IR_BACK_RIGHT_T)
specific(IR_BACK_RIGHT_PIXELS);
*/
/*
if(IR_FRONT_LEFT_READING> IR_LEAST_WHITE)
specific_clear(IR_FRONT_LEFT_PIXELS);
if(IR_FRONT_MID_READING> IR_LEAST_WHITE)
specific_clear(IR_FRONT_MID_PIXELS);
if(IR_FRONT_RIGHT_READING> IR_LEAST_WHITE)
specific_clear(IR_FRONT_RIGHT_PIXELS);


if(IR_BACK_LEFT_READING> 1000)
specific_clear(IR_BACK_LEFT_PIXELS);
if(IR_BACK_MID_READING> (IR_BACK_MID_T+F2))
specific_clear(IR_BACK_MID_PIXELS);
if(IR_BACK_RIGHT_READING> (IR_BACK_RIGHT_T+F2))
specific_clear(IR_BACK_RIGHT_PIXELS);
*/


while(Line_follower){

  IR_FRONT_LEFT_READING = analogRead(IR_FRONT_LEFT);
  IR_FRONT_MID_READING = analogRead(IR_FRONT_MID);
  IR_FRONT_RIGHT_READING = analogRead(IR_FRONT_RIGHT);
  IR_BACK_LEFT_READING = analogRead(IR_BACK_LEFT);
  IR_BACK_MID_READING = analogRead(IR_BACK_MID);
  IR_BACK_RIGHT_READING = analogRead(IR_BACK_RIGHT);

  if (IR_FRONT_LEFT_READING > IR_FRONT_LEFT_T && IR_FRONT_MID_READING < IR_FRONT_MID_T && IR_FRONT_RIGHT_READING > IR_FRONT_RIGHT_T) {
    forward(5);
    }
  if (IR_FRONT_LEFT_READING < IR_FRONT_LEFT_T && IR_FRONT_MID_READING > IR_FRONT_MID_T && IR_FRONT_RIGHT_READING > IR_FRONT_RIGHT_T) {
    forward_left(5); 
    }
  if (IR_FRONT_LEFT_READING > IR_FRONT_LEFT_T && IR_FRONT_MID_READING > IR_FRONT_MID_T && IR_FRONT_RIGHT_READING < IR_FRONT_RIGHT_T) {
    forward_right(5); 
    }
  if (IR_FRONT_LEFT_READING > IR_FRONT_LEFT_T && IR_FRONT_MID_READING > IR_FRONT_MID_T && IR_FRONT_RIGHT_READING > IR_FRONT_RIGHT_T 
  && IR_BACK_LEFT_READING > IR_BACK_LEFT_T && IR_BACK_MID_READING < IR_BACK_MID_T && IR_BACK_RIGHT_READING > IR_BACK_RIGHT_T ) {
    reverse(5); 
    }
  if (IR_FRONT_LEFT_READING > IR_FRONT_LEFT_T && IR_FRONT_MID_READING > IR_FRONT_MID_T && IR_FRONT_RIGHT_READING > IR_FRONT_RIGHT_T 
  && IR_BACK_LEFT_READING < IR_BACK_LEFT_T && IR_BACK_MID_READING > IR_BACK_MID_T && IR_BACK_RIGHT_READING > IR_BACK_RIGHT_T ) {
    reverse_left(5);
    }
  if (IR_FRONT_LEFT_READING > IR_FRONT_LEFT_T && IR_FRONT_MID_READING > IR_FRONT_MID_T && IR_FRONT_RIGHT_READING > IR_FRONT_RIGHT_T 
  && IR_BACK_LEFT_READING > IR_BACK_LEFT_T && IR_BACK_MID_READING > IR_BACK_MID_T && IR_BACK_RIGHT_READING < IR_BACK_RIGHT_T ) {
    reverse_right(5);
    }
  if (IR_FRONT_LEFT_READING < IR_FRONT_LEFT_T && IR_FRONT_MID_READING < IR_FRONT_MID_T && IR_FRONT_RIGHT_READING > IR_FRONT_RIGHT_T) {
    left(9);
    }
  if (IR_FRONT_LEFT_READING > IR_FRONT_LEFT_T && IR_FRONT_MID_READING < IR_FRONT_MID_T && IR_FRONT_RIGHT_READING < IR_FRONT_RIGHT_T) {
    right(9);
    }
  if (IR_FRONT_LEFT_READING < IR_FRONT_LEFT_T && IR_FRONT_MID_READING < IR_FRONT_MID_T && IR_FRONT_RIGHT_READING < IR_FRONT_RIGHT_T 
  && IR_BACK_LEFT_READING > IR_BACK_LEFT_T && IR_BACK_RIGHT_READING > IR_BACK_RIGHT_T ) {
    forward(5);
    }
  if (IR_FRONT_LEFT_READING > IR_FRONT_LEFT_T && IR_FRONT_MID_READING > IR_FRONT_MID_T && IR_FRONT_RIGHT_READING > IR_FRONT_RIGHT_T 
  && IR_BACK_LEFT_READING > IR_BACK_LEFT_T && IR_BACK_MID_READING > IR_BACK_MID_T && IR_BACK_RIGHT_READING > IR_BACK_RIGHT_T ) {
    STOP();
    }
    
}
}

void set_speed_right (int duty){
 if (duty == 1)
  duty = 2;
  ledcWrite (RIGHT_MOTORS,  map(duty,0,9,0,MAX_DUTY_CYCLE) );
}
void set_speed_left (int duty){
 if (duty == 1)
  duty = 2;
  ledcWrite (LEFT_MOTORS,  map(duty,0,9,0,MAX_DUTY_CYCLE) );
}
