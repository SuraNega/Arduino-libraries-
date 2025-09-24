#ifndef Gyro_Tomer_h
#define Gyro_Tomer_h

#include <Arduino.h>

class Gyro_Tomer
{
public:
  Gyro_Tomer();  // Constructor declaration
  void begin();
  void calibrate();
  float getYaw();
  void printYaw();
};

#endif
