#include <i2cdisplaycontroller.h>

#define DISPLAY_1 7 //display-1 switching pin
#define DISPLAY_1_DECIMAL_PIN 0
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
  display.setDelay(500);
  
  display.clear(); //clear the display, to avoid random data to be displayed.
}

void loop() {
  display.setDecimalPoint(DISPLAY_1_DECIMAL_PIN, DISPLAY_1, HIGH);
  display.getdelay(); // 500ms delay
  display.setDecimalPoint(DISPLAY_1_DECIMAL_PIN, DISPLAY_1, LOW);
  display.getdelay(); // 500ms delay
}
