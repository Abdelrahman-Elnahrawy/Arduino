/*

Voltaat Learn (http://learn.voltaat.com)

Link for full tutorial:

Tutorial: Building a device to read and graph heart rate using Arduino and ECG Sensor!

The purpose of this sketch is to build a device to read and chart the heart rate using

an Arduino board and an ECG sensor to capture vital signs. We will use a screen

to display the results visually.

Connections from the Arduino to the breadboard:

• Arduino 5V pin → Breadboard positive line

• Arduino GND pin → Breadboard ground line

Connections from the ECG Sensor:

• GND pin of the sensor → Breadboard ground line

• 3.3V pin of the sensor → 3.3V power pin on the Arduino board

• OUTPUT pin of the sensor → Analog pin A0 on the Arduino board

• LO- pin of the sensor → Digital pin 11 on the Arduino board

• LO+ pin of the sensor → Digital pin 10 on the Arduino board

Connections from the OLED display:

• VCC pin → Breadboard 5V line

• GND pin → Breadboard GND line

• SDA pin → Arduino analog pin A4

• SCL pin → Arduino analog pin A5

*/

#include "U8glib.h"

// Initialize U8glib display (SH1106 128x64) using I2C protocol

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);

// Define the biosensor input pin

#define SENSOR A0

// Define the threshold for detecting a heartbeat

#define Highpulse 550

// Variables for graphing and pulse calculation

int x = 0;        // Current X position for drawing the signal

int Svalue = 0;   // Raw sensor reading

int value = 0;    // Mapped value for display range

long Stime = 0;   // Current time of pulse measurement

long Ltime = 0;   // Last recorded time for pulse

int count = 0;    // Pulse count

int Bpm = 0;      // Calculated BPM (beats per minute)

// Variables for calculating average BPM

unsigned long beat_old = 0;

int beatIndex = 0;

float beats[200]; // Array to store BPM values for averaging

// Array to store graph data

int graphData[128];

int prevY = 0; // Previous Y position for drawing the graph

void setup() {

   u8g.setFont(u8g_font_helvB12); // Set default font

   u8g.setColorIndex(1); // Set color to white (for monochrome screens)

   // Initialize the graph data to the middle position

   for (int i = 0; i < 128; i++) {

       graphData[i] = 128;

   }

}

void loop() {

   // Read the sensor value

   Svalue = analogRead(SENSOR);

   

   // Map the sensor value to a suitable range for graphing

   value = map(Svalue, 0, 1024, 0, 45);

   

   // Store the current value in the graph data array

   graphData[x] = 60 - value;

   

   // Wait briefly to prevent data saturation

   delay(4);

   

   // Update graph position

   x++;

   if (x >= 128) { // Reset position if it exceeds the screen width

       

       // Update the display to show the graph

       u8g.firstPage();

       do {

           for (int i = 1; i < x; i++) {

               int y1 = graphData[i - 1]; // Previous graph value

               int y2 = graphData[i];     // Current graph value

               u8g.drawLine(i - 1, y1, i, y2); // Draw line between points

           }

           drawBPM();

       } while (u8g.nextPage());

       

       // Reset graph position and clear old data

       x = 0;

       for (int i = 0; i < 128; i++) {

           graphData[i] = 128;

       }

   }

   BPM(); // Calculate the BPM

}

void drawBPM() {

   // Display the BPM text

   u8g.setPrintPos(0, 12); // Set text position

   u8g.print("BPM: "); // Print BPM label

   u8g.print(Bpm); // Print the BPM value

}

void BPM() {

   if (Svalue > Highpulse) { // Detect a heartbeat

       Stime = millis() - Ltime; // Calculate time since last pulse

       count++; // Increment pulse count

       

       if (Stime / 1000 >= 10) { // If 10 seconds have passed

           Ltime = millis(); // Reset last recorded time

           Bpm = (count * 6); // Calculate BPM (extrapolate to 60 seconds)

           count = 0; // Reset pulse count

       }

   }

}