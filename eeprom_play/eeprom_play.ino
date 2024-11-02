/**
 * This sketch shows examples on how to use all the features of this library
 * 
 * It can also be used as a test  to verify that you have your eprom configured
 * propery to your Arduino as it prints out the results so you can see if everything works
 */

#include <at24c256.h>

// Create a eprom object configured at address 0
// Sketch assumes that there is an eprom present at this address
AT24C256 eprom(AT24C_ADDRESS_0);
// Create another eprom object configured att address 2
// Sketch assumes that there is NO eprom present at this address
AT24C256 badEprom(AT24C_ADDRESS_2);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting up");

  // Initialize the i2c library
  Wire.begin();

  /** Write and read an integer */
  int foo = 42;
  // Write the integer foo to the eprom starting at address 0
  eprom.put(0, foo);
  int foo_in;
  // Read the integer foo_in from eprom starting at address 0
  eprom.get(0, foo_in);
  Serial.println(foo_in);

}

// This test program has no loop, it just runs once
void loop() {
}
