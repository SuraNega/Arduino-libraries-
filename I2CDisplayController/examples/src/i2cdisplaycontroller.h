// FILE: i2c7seg.h
// AUTHOR: Aditya Chaudhary
// DATE: 25-06-2023
// VERSION: 0.0.1
// PURPOSE: Arduino library for Seven Segment Display with I2C Communication Interface.
// URL:
#ifndef i2cdisplaycontroller_h
#define i2cdisplaycontroller_h

#include "Arduino.h"
#include "Wire.h"

#ifndef i2c7seg_INITIAL_VALUE // If not defined
#define i2c7seg_INITIAL_VALUE 0xFF
#endif

#define i2c7seg_OK 0x00
#define i2c7seg_PIN_ERROR 0x81
#define i2c7seg_I2C_ERROR 0x82

class I2CDisplayController
{

public:
  I2CDisplayController(TwoWire *wire = &Wire);
  bool begin();
  bool autoAddressDetection();


  bool setAddress(const uint8_t deviceAddress);
  uint8_t getAddress();

  void setDisplayConfiguration(bool commonAnode);
  void setDigitsPort(bool portselect);

  void executeI2C_Commands();

  uint8_t print(const uint8_t display_value, const uint8_t switching_pin);
  uint8_t turnOff(const uint8_t switching_pin);
  void clear();

  uint8_t setDecimalPoint(const uint8_t decimal_pin, const uint8_t switching_pin, bool status); // pin at which dp is connected.

  void setDelay(int m_delay);
  void getdelay();

  int lastError();

private:
  uint8_t _address;
  bool _commonAnode;
  bool _port0select;
  int milli_delay;
  uint8_t _dataIn;
  uint8_t _switching_value;
  uint8_t _error;
  uint8_t _pin_error;
  uint8_t _OK;

  TwoWire *_wire;
};

#endif
//  -- END OF FILE --