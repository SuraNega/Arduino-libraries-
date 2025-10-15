#include <i2cdisplaycontroller.h>

#define DISPLAY_1 7 //display-1 switching pin
/*
  If you are using multiple displays.
  #define DISPLAY_2 6
  #define DISPLAY_3 5
  #define DISPLAY_4 4
 */

I2CDisplayController display;


void setup() {

  /* Initial settings */
  display.begin(); //connection with PCF8575
  display.setDigitsPort(false); //if your digits are not on PORT 0 pass false. It is advisable to follow wiring diagram.
  display.setDisplayConfiguration(true); //if you are using common anode display pass true, bydefault it is common cathode.

  display.setDelay(3); //use this while multiplexing.
}

void loop() {/*Nothing*/}
