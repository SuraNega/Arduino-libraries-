//=====================================================
//=== ************** SAMPLES of CODE ************** ===
//=====================================================
#include <Amytol_Sample.h>
//=====================================================
//=== ************ Declarations ******************* ===
//=====================================================
#define LED
 const int LED_Green = 11;
 const int LED_Amber = 12;
 const int LED_Red = 13;

#define PIXELSTRIPS
 #include <FastLED.h>
 const int  NUM_LEDS = 4;
 const int  FastLED_Pin_F = 9;
 const int  FastLED_Pin_R = 10;
 CRGB leds[NUM_LEDS];
 CRGB leds_R[NUM_LEDS];

 unsigned long prvMilsNEO_F = 2600UL;
 unsigned long prvMilsNEO_R = 2600UL;
 unsigned long prvMilsLED_G = 2600UL;
 unsigned long prvMilsLED_A = 2600UL;
 unsigned long prvMilsLED_R = 2600UL;
 unsigned long inter250 = 250UL;
 unsigned long inter500 = 500UL;
 unsigned long inter750 = 750UL;
 unsigned long inter1000 = 1000UL;

//#define MOTORS
 const int _mlpin = 6;
 const int _lpinF = 4;
 const int _lpinR = 7;
 const int _mrpin = 5;
 const int _rpinF = 3;
 const int _rpinR = 2;

//#define SERVO
 #include <Servo.h>  //Arduino IDE included Servo motor library
 Servo servo_motor; //Name for our servo motor

#define ULTRASONIC
 #include <NewPing.h>
 const int  trig_pin = A1; //analog input 1
 const int  echo_pin = A1 ;//analog input 2 if Grove one pin use same pin
 const int maximum_distance = 200;
 NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
 int distance = 100;
 unsigned long time_now = 0UL;
//=====================================================
//=== ************* Set Up.   ********************* ===
//=====================================================
void setup()
{
#ifdef PIXELSTRIPS
  FastLED.addLeds<NEOPIXEL, FastLED_Pin_F>(leds, NUM_LEDS);//GRB ordering is assumed
  FastLED.addLeds<NEOPIXEL, FastLED_Pin_R>(leds, NUM_LEDS);
 // FastLED.addLeds<WS2812, FastLED_Pin_F, RGB>(leds, NUM_LEDS);//GRB order is typical

#endif
#ifdef MOTORS
  pinMode( _mlpin, OUTPUT );  // Channel A enable
  pinMode( _lpinF, OUTPUT ); // Channel A input 1
  pinMode( _lpinR, OUTPUT ); // Channel A input 2
  pinMode( _mrpin, OUTPUT );  // Channel B enable
  pinMode( _rpinF, OUTPUT ); // Channel B input 3
  pinMode( _rpinR, OUTPUT ); // Channel B input 4
#endif
#ifdef SERVO

  servo_motor.attach(8); // Setup servo
  //wait(500);  // Give Time to initalise Delay the motion
  servo_motor.write(120);
  //wait(2000);


#endif
#ifdef ULTRASONIC
  distance = readPing();
  wait(100);
  Serial.println(distance);
#endif
Serial.begin( 9600 );
}
//=====================================================
//=== **************** Loop *********************** ===
//=====================================================
void loop()
{unsigned long currentMillis = millis(); // Current Time

#ifdef LED
 pinMode(LED_Green, OUTPUT);
 pinMode(LED_Amber, OUTPUT);
 pinMode(LED_Red, OUTPUT);

 if (currentMillis - prvMilsLED_G > 100)
 {digitalWrite(LED_Green, HIGH);}
 if (currentMillis - prvMilsLED_G > 350)
 {digitalWrite(LED_Green, LOW);  prvMilsLED_G = currentMillis;}
 
 if (currentMillis - prvMilsLED_A > 220)
 {digitalWrite(LED_Amber, HIGH);}
 if (currentMillis - prvMilsLED_A > 470)
 {digitalWrite(LED_Amber, LOW);  prvMilsLED_A = currentMillis;}

 if (currentMillis - prvMilsLED_R > 330)
 {digitalWrite(LED_Red, HIGH);}
 if (currentMillis - prvMilsLED_R > 580)
 {digitalWrite(LED_Red, LOW);  prvMilsLED_R = currentMillis;}
 #endif

#ifdef PIXELSTRIPS
 if (currentMillis - prvMilsNEO_F > inter500)
 {flashOn(); }
 if (currentMillis - prvMilsNEO_F > inter1000)
 {flashOff();  prvMilsNEO_F = currentMillis;}
 
 if (currentMillis - prvMilsNEO_R > inter250)
 {flashOn_R(); }
 if (currentMillis - prvMilsNEO_R > inter750)
 {flashOff_R();  prvMilsNEO_R = currentMillis;}
#endif
#ifdef MOTORS
      Serial.println("forward");
      setMotor(255, HIGH, LOW, 255, HIGH, LOW);//Forward
      delay(5000);
      allInputsOff();

      Serial.println("turnRight");
      setMotor(255, HIGH, LOW, 255, LOW, HIGH);//turnRight
  
      delay(5000);
      allInputsOff();
      
      Serial.println("turnLeft");
      setMotor(255, LOW, HIGH,255, HIGH, LOW);//turnLeft
  
      delay(5000);
      allInputsOff();
      Serial.println("reverse");
      setMotor(255, LOW, HIGH, 255, LOW, HIGH);//Reverse
      delay(5000);
      allInputsOff();
      
      Serial.println("forward half speed");
      setMotor(255, LOW, HIGH, 147, LOW, HIGH);//forward half speed
      delay(5000);
      allInputsOff();
#endif
#ifdef SERVO
   servo_motor.write(50);
   delay(500);
   servo_motor.write(100);
   delay(500);
   servo_motor.write(150);
   delay(500);
   servo_motor.write(100);
   delay(500);
   
#endif
#ifdef ULTRASONIC
 distance = readPing();
 Serial.println(distance);
#endif
}
//=====================================================
//=== ************* Functions ********************* ===
//=====================================================

#ifdef LED
void allInputsOff()
{
  digitalWrite( 4, LOW );
  digitalWrite( 7, LOW );
  digitalWrite( 6, LOW );
  digitalWrite( 3, LOW );
  digitalWrite( 2, LOW );
  digitalWrite( 5, LOW );
}

void setMotor(int PWML, int fwrdBackFL, int fwrdBackRL, int PWMR, int fwrdBackFR, int fwrdBackRR) {
// Set PWM Duty Cycle value between 0 and 255
// Set Direction 
  digitalWrite(_lpinF, fwrdBackFL);
  digitalWrite(_lpinR, fwrdBackRL);
  digitalWrite(_rpinF, fwrdBackFR);
  digitalWrite(_rpinR, fwrdBackRR);
  setSpeed(PWML,PWMR);
 }
void setSpeed(int PWML,int PWMR) {
  analogWrite(_mlpin, PWML);
  analogWrite(_mrpin, PWMR);
}
// LED
void led_on() {
  digitalWrite(LED_Green, HIGH);
  digitalWrite(LED_Amber, HIGH);
  digitalWrite(LED_Red, HIGH);
}
void led_green() {
  digitalWrite(LED_Green, HIGH);
  digitalWrite(LED_Amber, LOW);
  digitalWrite(LED_Red, LOW);      
} 
void led_amber() {
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Amber, HIGH);
  digitalWrite(LED_Red, LOW);
}
void led_red() {
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Amber, LOW);
  digitalWrite(LED_Red, HIGH);
}

void led_off() {
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Amber, LOW);
  digitalWrite(LED_Red, LOW);
}
#endif
#ifdef PIXELSTRIPS
void flashOff(){
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}
void flashOn(){
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
}
void flashOff_R(){
  fill_solid(leds_R, NUM_LEDS, CRGB::Black);
  FastLED.show();
}
void flashOn_R(){
  fill_solid(leds_R, NUM_LEDS, CRGB::Red);
  FastLED.show();
}
void flashRAG(){
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
#endif
#ifdef ULTRASONIC
  int readPing()
  {
  wait(70);
    int cm = sonar.ping_cm();
    if (cm==0){
    cm=2500;
  }
    return cm;}

void wait(unsigned long wait_Time) {
time_now = millis();
while(millis() < time_now + wait_Time){}
}
#endif
