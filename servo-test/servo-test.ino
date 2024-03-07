/*
 * Servo test
 * 
 * These project use I2C to communicate, 2 pins are required to interface. 
 * 
 * For Arduino UNO:
 *    pin   | signal
 * ---------|-------
 * Analog 5 |  SCL
 * Analog 4 |  SDA
 */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm0 = Adafruit_PWMServoDriver();

#define SERVOMIN  120
#define SERVOMAX  470
#define SERVO_FREQ 50

#define SERVO 0 //servo number

void setup() {
  Serial.begin(9600);
  Serial.println("Servo test running");
  
  pwm0.begin();
  pwm0.setOscillatorFrequency(27000000);
  pwm0.setPWMFreq(SERVO_FREQ);
  
  delay(10);
}

void loop() {

  moveServo(0);
  moveServo(90);
  moveServo(180);
  moveServo(90);   //-90

 Serial.println("--- end loop ---"); 
}

void moveServo(int angle) {

  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX); //angle to pulse
  pwm0.setPWM(SERVO, 0, pulse);

  //display infos
  Serial.print("angle: "); Serial.print(angle); Serial.print("°");
  Serial.print(" pulse: "); Serial.println(pulse);

  delay(2000);
}
