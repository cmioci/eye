/*
 * Servo test with button
 * 
 * These project use I2C to communicate, 2 pins are required to interface. 
 * 
 * For Arduino UNO:
 *    pin   | signal
 * ---------|-------
 * Analog 5 |  SCL
 * Analog 4 |  SDA
 * 
 */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm0 = Adafruit_PWMServoDriver();

#define PIN_BUTTON 2

//use caution when adjusting SERVO_MIN and SERVO_MAX. Hitting the physical 
//limits of travel can strip the gears and permanently damage your servo
#define SERVO_MIN  120   //this is the 'minimum' pulse length count (out of 4096)
#define SERVO_MAX  470   //this is the 'maximum' pulse length count (out of 4096)

#define SERVO_FREQ 50

#define SERVO 0 //servo number

int   buttonState = 0;
int   steps = 0;
int   angle = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Servo test running");

  pinMode(PIN_BUTTON, INPUT_PULLUP);  //use internal arduino resistor
  
  pwm0.begin();
  pwm0.setOscillatorFrequency(27000000);
  pwm0.setPWMFreq(SERVO_FREQ);
  
  delay(10);
}

void loop() {

  buttonState = digitalRead(PIN_BUTTON);

  if (buttonState == LOW) {
    
    if(steps == 0) {
      angle = 0;
    }
    else if(steps == 1) {
      angle = 45;
    }
    else if(steps == 2) {
      angle = 90;
    }
    else if(steps == 3) {
      angle = 135;
    }
    else if(steps == 4) {
      angle = 180;
    }
    else if(steps == 5) {
      angle = 135;
    }
    else if(steps == 6) {
      angle = 90;
    }
    else if(steps == 7) {
      angle = 45;
    }
    
    moveServo(angle);
    
    if( steps++ >= 7 ) {
      steps = 0;
    }
  }

  delay(500);
  
}

void moveServo(int angle) {

  //map angle of 0 to 180 to servo min and servo max 
  int pulse = map(angle, 0, 180, SERVO_MIN, SERVO_MAX); //angle2pulse
  pwm0.setPWM(SERVO, 0, pulse);

  //display infos
  Serial.print("angle: "); Serial.print(angle); Serial.print("°");
  Serial.print(" pulse: "); Serial.println(pulse);
}
