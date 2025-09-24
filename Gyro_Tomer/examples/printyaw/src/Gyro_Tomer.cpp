#include "Gyro_Tomer.h"
#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 gyrosensor(Wire);

// Constructor definition
Gyro_Tomer::Gyro_Tomer()
{
  // Constructor code here, if needed
}

void Gyro_Tomer::begin()
{
  Serial.begin(115200);
  calibrate();
  gyrosensor.calcGyroOffsets();
  Wire.begin();
  // gyrosensor.setGyroOffsets(30, 14, 18);

}

void Gyro_Tomer::calibrate()
{
  Serial.begin(115200);
  Wire.begin();

  gyrosensor.setGyroOffsets(-54, -36, 26);
	gyrosensor.setAccOffsets(-598,  -789, 2126);

  byte status = gyrosensor.begin();
  Serial.print("Gyro status: ");
  Serial.println(status);
  if (status != 0) {
    Serial.println("Gyro failed... Check wiring and power supply.");
    while (1);
}
  
  Serial.println("Calculating the offsets, Don't move your gyro");
  delay(1000);
  gyrosensor.calcOffsets(); 
  Serial.println("Done!\n");}

float Gyro_Tomer::getYaw() {
  gyrosensor.update();
  float yaw = gyrosensor.getAngleZ();

  if (yaw > 360) {
    yaw -= 360;
  } else if (yaw < -360) {
    yaw += 360;
  }

  return yaw;
}


void Gyro_Tomer::printYaw(){
  Serial.print("Yaw: ");
  Serial.println(getYaw());
}