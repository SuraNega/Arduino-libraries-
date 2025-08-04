//20231001

//https://www.digikey.com.au/en/maker/blogs/2022/how-to-avoid-using-the-delay-function-in-arduino-sketches
//https://www.youtube.com/watch?v=HHFxVHWo97o
//https://github.com/danf42/arduino-obstacle-avoidance-robot/tree/master
//https://github.com/kigster/obstacle-avoiding-robot/tree/master

//https://www.baldengineer.com/millis-tutorial.html
#include <AmytolRC.h>
#include <Servo.h>  //Arduino IDE included Servo motor library
#include <FastLED.h>
#define NEXTGEN     // NextGen CodeCamp Specifics
#define NUM_LEDS 4
#define DATA_PIN 12
CRGB leds[NUM_LEDS];
int robotStatus ;
// PINS to set up the pins as outputs:
Rbt rbt (007); //Secret Agent Pin Declaration 
//Ultrasonic sensor pins J8 Nexgen Rover v3
const int  trig_pin = A1; //analog input 1
const int  echo_pin = A1 ;//analog input 2 if Grove one pin use same pin
//Ultrasonic sensor pins J3 Nexgen Rover v3
//const int trig_pin = 7;
//const int echo_pin = 7;
//Ultrasonic sensor pins J8 Nexgen Rover v3
//const int trig_pin = A5; //analog input 1
//const int echo_pin = A5; //analog input 2 if Grove one pin use same pin
// each LED gets a state varaible
boolean LED13state = false; //the LED will turn ON in the first iteration of loop()
boolean LED12state = false; // need to seed the light to be OFF
//unsigned long previousMillis = 0UL;
unsigned long time_now = 0UL;
unsigned long time_now1 = 0UL;
unsigned long time_now2 = 0UL;
unsigned long millisForward= 0UL;
unsigned long millisSpeed= 0UL;
unsigned long millisHardStop= 0UL;
unsigned long millisCoastStop= 0UL;
unsigned long millisStop= 0UL;

unsigned long prevMillis = 2600UL;
unsigned long prevMillis1 = 2600UL;
unsigned long prevMillis2 = 2600UL;
unsigned long prevMillis3 = 2600UL;
unsigned long prevMillis4 = 2600UL;
unsigned long prevMillis5 = 2600UL;
unsigned long prevMillis6 = 2600UL;
unsigned long inter50 = 50UL;
unsigned long inter500 = 500UL;
unsigned long inter1000 = 1000UL;
int robotDirection;
int robotMotion ;


const int fPWM = 250; //Forward speed
const int tuningLeftMotor = 90; //Extend PMW value if Left Motor is slower
const int tuningRightMotor = 0;//Extend PMW value if Right Motor is slower
const int fPWML = fPWM - tuningRightMotor; 
const int fPWMR = fPWM - tuningLeftMotor; 


const int maximum_distance = 200;
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function

//NewPing(uint8_t trigger_pin, uint8_t echo_pin, unsigned int max_cm_distance = MAX_SENSOR_DISTANCE)


Servo servo_motor; //Name for our servo motor



 const int _lpin  = 4; // dirLPin direction left pin connected to the motor
 const int _rpin  = 7; // dirRPin direction right pin connected to the motor
const int _mlpin = 6; // motorLPin PWM output connected to PWM A
 const int _mrpin = 5; // motorRPin PWM output connected to the motor right pin
 


void setup()        // Where we setup the initalising code which run one
{
 // rbt.begin();   // Initalise the Workspace
  Serial.begin(9600);
  pinMode(_lpin, OUTPUT);
  pinMode(_rpin, OUTPUT);
  pinMode(_mlpin, OUTPUT);
  pinMode(_mrpin, OUTPUT);

      FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
     FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
     flashOff();
  servo_motor.attach(4); // Setup servo
  wait(500);  // Give Time to initalise Delay the motion
  servo_motor.write(90);
  wait(2000);
  distance = readPing();
  wait(100);
  Serial.println(distance);
} 
void loop() {         // Continualy repeats unless told to stop  
  int distanceRight = 0;
  int distanceLeft = 0;
  unsigned long currentMillis = millis(); // Current Time
 // if(currentMillis - prevMillis > inter50)
 // {


     



    //  robotDirection = 1; //Forward
    //  robotMotion = 0; //Stopped
    //    if(robotDirection == 1 && robotMotion == 0)
     //   {rbt.setMotor(190,250, HIGH, HIGH);
     //   robotMotion = 1;}
      //  if(robotDirection == 1 && robotMotion == 1 && currentMillis - prevMillis  > 450)
       // {
       
       
       //   rbt.setSpeed(0,0); 
          rbt.setMotor(190,250, HIGH, HIGH);
        //}



// }






 

}

//=====================================================
//=== ************* Functions ********************* ===
//=====================================================

void wait(unsigned long wait_Time) {
time_now = millis();
while(millis() < time_now + wait_Time){}

}
int lookRight(){ 
  servo_motor.write(20);
  wait(500);
  int distance = readPing();
  wait(100);
  servo_motor.write(90);
  return distance;
}
int lookLeft(){
  servo_motor.write(160);
  wait(500);
  int distance = readPing();
  wait(100);
  servo_motor.write(90);
  return distance;
  wait(100);
 
}
int readPing(){
  wait(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void flashOff(){
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}
void flashOn(){
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
}
void flashFRBL(){
if(robotStatus == 1){
  leds[1] = CRGB::Red;
  leds[2] = CRGB::Red;
  leds[3] = CRGB::Red;
  FastLED.show();
  delay(500);
  leds[1] = CRGB::Black;
  leds[2] = CRGB::Black;
  leds[3] = CRGB::Black;
  FastLED.show();
  delay(500);
}
}



