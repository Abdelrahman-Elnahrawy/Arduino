
/* MOTOR PINS  DEFINITION (.h) */
#include <Ps3Controller.h>

#define factor 0.5

#define MOTOR1_1  4        // L298N #1 in 1 motor Front Right ORANGE AT 4 TO PURPLE AT 19 YELLWOW AR 22 GREEN AT 23
#define MOTOR2_1  16        // L298N #1 in 2 motor Front Right
#define MOTOR1_2  17       // L298N #1 in 3 motor Back Right
#define MOTOR2_2  5       // L298N #1 in 4 motor Back Right

#define MOTOR3_1  19        // L298N #2 in 1 motor Front Left
#define MOTOR3_2  18        // L298N #2 in 2 motor Front Left
#define MOTOR4_2  23       // L298N #2 in 3 motor Back Left
#define MOTOR4_1  22       // L298N #2 in 4 motor Back Left


/*PWM DEFINTTIONS (.h)*/

#define MOTOR3_4_EN 15
#define MOTOR1_2_EN 13

#define PWMFreq        1000
#define RIGHT_MOTORS   1   //THE CHANNEL OF PWM
#define LEFT_MOTORS    0  //THE CHANNEL OF PWM
#define PWMResolution  6

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
void STOP() {
  digitalWrite(MOTOR1_1, HIGH);
  digitalWrite(MOTOR1_2, HIGH );
  digitalWrite(MOTOR2_1, HIGH);
  digitalWrite(MOTOR2_2, HIGH);
  digitalWrite(MOTOR3_1, HIGH);
  digitalWrite(MOTOR3_2, HIGH );
  digitalWrite(MOTOR4_1, HIGH);
  digitalWrite(MOTOR4_2, HIGH );

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
boolean restart = 0;

void notify()
{
  //--- Digital cross/square/triangle/circle button events ---
  if ( Ps3.event.button_down.cross ){
    Serial.println("Started pressing the cross button");
    if (Ps3.data.analog.button.cross == 255) 
       {/*##################################################################################################################*/
       forward_left(9);
       }
  }
  if ( Ps3.event.button_up.cross )
    Serial.println("Released the cross button");

  if ( Ps3.event.button_down.square ){
    Serial.println("Started pressing the square button");
     if (Ps3.data.analog.button.square == 255) 
       {/*##################################################################################################################*/
       reverse_left(9);
       }
  }
  if ( Ps3.event.button_up.square )
    Serial.println("Released the square button");

  if ( Ps3.event.button_down.triangle ){
    Serial.println("Started pressing the triangle button");
    if (Ps3.data.analog.button.triangle == 255) 
       {/*##################################################################################################################*/
       forward_right(9);
       }
  }
  if ( Ps3.event.button_up.triangle )
    Serial.println("Released the triangle button");

  if ( Ps3.event.button_down.circle ){
    Serial.println("Started pressing the circle button");
    if (Ps3.data.analog.button.circle == 255) 
       {/*##################################################################################################################*/
       reverse_right(9);
       }
  }
  if ( Ps3.event.button_up.circle )
    Serial.println("Released the circle button");

  //--------------- Digital D-pad button events --------------
  if ( Ps3.event.button_down.up )
    Serial.println("Started pressing the up button");
  if ( Ps3.event.button_up.up ) {
    Serial.println("Released the up button");
    STOP();
  }/*FORWARD####FORWARD####FORWARD####FORWARD####FORWARD####FORWARD####FORWARD####FORWARD####FORWARD####FORWARD*/

  if ( Ps3.event.button_down.right )
    Serial.println("Started pressing the right button");
  if ( Ps3.event.button_up.right )
    Serial.println("Released the right button");

  if ( Ps3.event.button_down.down )
    Serial.println("Started pressing the down button");
  if ( Ps3.event.button_up.down ) {
    Serial.println("Released the down button");
    STOP();
  }
  if ( Ps3.event.button_down.left )
    Serial.println("Started pressing the left button");
  if ( Ps3.event.button_up.left )
    Serial.println("Released the left button");

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
  if ( Ps3.event.button_up.select )
    Serial.println("Released the select button");

  if ( Ps3.event.button_down.start )
    Serial.println("Started pressing the start button");
  if ( Ps3.event.button_up.start )
    Serial.println("Released the start button");

  if ( Ps3.event.button_down.ps )
    Serial.println("Started pressing the Playstation button");
  if ( Ps3.event.button_up.ps )
    Serial.println("Released the Playstation button");


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
      forward(9);
    }
  }

  if ( abs(Ps3.event.analog_changed.button.right) ) {
    Serial.print("Pressing the right button: ");
    Serial.println(Ps3.data.analog.button.right, DEC);
  }

  if ( abs(Ps3.event.analog_changed.button.down) ) {
    Serial.print("Pressing the down button: ");
    Serial.println(Ps3.data.analog.button.down, DEC);
    if (Ps3.data.analog.button.down == 255) {/*##################################################################################################################*/
      reverse(9);
    }
  }

  if ( abs(Ps3.event.analog_changed.button.left) ) {
    Serial.print("Pressing the left button: ");
    Serial.println(Ps3.data.analog.button.left, DEC);
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
  }

  if ( abs(Ps3.event.analog_changed.button.circle) ) {
    Serial.print("Pressing the circle button: ");
    Serial.println(Ps3.data.analog.button.circle, DEC);
  }

  if ( abs(Ps3.event.analog_changed.button.cross) ) {
    Serial.print("Pressing the cross button: ");
    Serial.println(Ps3.data.analog.button.cross, DEC);
  }

  if ( abs(Ps3.event.analog_changed.button.square) ) {
    Serial.print("Pressing the square button: ");
    Serial.println(Ps3.data.analog.button.square, DEC);
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

void onConnect() {
  Serial.println("Connected.");
}
















// TO TILT SLIGHTLY LEFT OR RIGHT U CAN CHANGE THE SPEED OF THE SIDE
void setup() {



  Serial.begin(115200);

  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("00:1a:7d:da:71:10");
  Serial.println("Ready.");








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
  pinMode(MOTOR1_2, OUTPUT);
  pinMode(MOTOR2_2, OUTPUT);

  pinMode(MOTOR3_1, OUTPUT);
  pinMode(MOTOR3_2, OUTPUT);
  pinMode(MOTOR4_2, OUTPUT);
  pinMode(MOTOR4_1, OUTPUT);

  digitalWrite(MOTOR3_1, HIGH  );
  digitalWrite(MOTOR3_2, HIGH );
}


void loop() {

  while (!Ps3.isConnected()) {
    if (!restart) {
      Serial.println("not connected");
      Serial.println("restart in 10 seconds if not connected");
      time_till_res = millis();
      restart = 1;
    }

    if (millis() - time_till_res > 10000) {
      ESP.restart();
    }


  }

}

void set_speed_right (int duty) {
  if (duty == 1)
    duty = 2;
  ledcWrite (RIGHT_MOTORS,  map(duty, 0, 9, 0, MAX_DUTY_CYCLE) );
}
void set_speed_left (int duty) {
  if (duty == 1)
    duty = 2;
  ledcWrite (LEFT_MOTORS,  map(duty, 0, 9, 0, MAX_DUTY_CYCLE) );
}
