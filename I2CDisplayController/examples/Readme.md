## I2CDisplayController
I2CDisplayController is an Arduino library designed to simplify the process of driving 7-segment displays using the PCF8575 I2C IO expander. It provides an intuitive interface for controlling multiple displays through I2C communication, making it ideal for Arduino enthusiasts, hobbyists, and developers. It enables the creation of various projects involving numerical or alphanumeric displays, such as clocks, temperature monitors, and counters.

## Features
- Easy integration: The library abstracts the complexity of controlling 7-segment displays with the PCF8575 I2C IO expander, allowing you to focus on your project's functionality.
- I2C communication: Utilize the I2C protocol for seamless communication between your Arduino board and the PCF8575 IC.
- Flexible digit port selection: Choose between two ports (Port 0 and Port 1) for connecting your 7-segment display digits, providing flexibility in hardware setup.
- Decimal point control: Easily set or remove decimal points for individual digits.
- Display control functions: Turn off specific digits or clear the entire display with simple function calls.
- Auto address detection: The library includes an automatic address detection feature to simplify the setup process and detect the PCF8575's I2C address automatically.

## Wiring Diagram
![](https://github.com/addy123d/I2CDisplayController/blob/main/extras/schematic.png)

## Display Configuration
The I2CDisplayController library provides flexible configuration options for driving 7-segment displays using the PCF8575 I2C IO expander. This section will guide you on how to configure the library to suit your specific display setup.

### Digit Port Selection
The library allows you to choose between two ports (Port 0 and Port 1) for connecting your 7-segment display digits. This selection is important to ensure proper mapping of the display segments to the corresponding IO pins on the PCF8575. By default, Port 0 is selected.

To change the digit port selection, use the following function:

```
display.setDigitsPort(portselect);
```
Set portselect to true to select Port 0 or false to select Port 1.

### Common Anode or Common Cathode Configuration
The library supports both common anode and common cathode configurations for the 7-segment displays. The configuration determines the logic for turning on/off the segments of the display.

By default, the library assumes a common cathode configuration. If your display is common anode, you need to set the common anode flag using the following function:

```
display.setCommonAnode(true);
```
Set true if your display is common anode, or false if it is common cathode.

### Decimal Point Control
The library allows you to set or remove the decimal point for individual digits on the display. This is useful for displaying decimal values or adding visual emphasis to specific digits.

To set or remove the decimal point for a digit, use the following function:

```
display.setDecimalPoint(decimal_pin, switching_pin, status);
```
- decimal_pin is the pin number of the decimal point (0-7).
- switching_pin is the pin number of the switching pin corresponding to the digit (0-7).
- status should be set to true to set the decimal point or false to remove it.

Make sure to adjust the decimal_pin and switching_pin values according to your specific display configuration

## Getting Started
### Display Characters
```c
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
  display.setDelay(500);

  //print 0 - F on display
  for(int i = 0; i < 16; i++){
    display.print(digitToSegment[i], DISPLAY_1);
    
    display.getdelay(); //create delay.
  }
}

void loop() {/*Nothing*/}
```


##  Contributing
Contributions to the I2CDisplayController library are welcome! If you find any issues or have suggestions for improvements, please open an issue on the [I2CDisplayController Repository](https://github.com/addy123d/I2CDisplayController/issues) or submit a pull request.

## License
This library is released under the [MIT LICENSE](https://github.com/addy123d/I2CDisplayController/blob/main/LICENSE). Please review the license file for more information.