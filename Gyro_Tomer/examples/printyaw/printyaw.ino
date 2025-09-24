#include "Gyro_Tomer.h"
#include <Arduino.h>
#include <Wire.h>
#include <MPU6050_light.h>


Gyro_Tomer gyro; //Name your MPU6050 (everything except gyrosensor)

//fubctions:
    //getYaw: return the current yaw angle.
    //begin: begins the MPU6050.
    //calibrate: calibrates(reset) the MPU6050.
    //printYaw: Serial print the current yaw angle.

void setup() {
  gyro.begin();
}

void loop() {
  gyro.printYaw();
}
