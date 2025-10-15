#include <i2cdisplaycontroller.h>

#define DISPLAY_1 7 //display-1 switching pin, dec
/*
  If you are using multiple displays.
  #define DISPLAY_2 6
  #define DISPLAY_3 5
  #define DISPLAY_4 4
 */

I2CDisplayController display;

//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---  .X 
//      D

const uint8_t digitToSegment[] = {
 // XGFEDCBA
  0b00111111,    // 0
  0b00000110,    // 1
  0b01011011,    // 2
  0b01001111,    // 3
  0b01100110,    // 4
  0b01101101,    // 5
  0b01111101,    // 6
  0b00000111,    // 7
  0b01111111,    // 8
  0b01101111,    // 9
  0b01110111,    // A
  0b01111100,    // b
  0b00111001,    // C
  0b01011110,    // d
  0b01111001,    // E
  0b01110001     // F
  };


void setup() {

  /* Initial settings */
  display.begin(); //connection with PCF8575
  //display.setDigitsPort(false); //Uncomment this line, if your digits are not on PORT 0. It is advisable to follow wiring diagram.
  //display.setDisplayConfiguration(true); //Uncomment this line, if you are using common anode display, bydefault it is common cathode.

  display.setDelay(500);

  //print 0 - F on display
  for(int i = 0; i < 16; i++){
    display.print(digitToSegment[i], DISPLAY_1);
    
    display.getdelay(); //create delay.
  }
}

void loop() {/*Nothing*/}
