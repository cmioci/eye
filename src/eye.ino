/* filename...: eye.ino
 * project....: Eye mechanism
 * creation...: 28/02/2024
 * updated....: 28/02/2024
 * ArduinoSoftware(IDE): 1.8.9
 * WebInfo.............: ---
 * author.....: cmioci
 * description: 
 */
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/*-----------------------------------------------------------------------------
 * COSTANTs
 *---------------------------------------------------------------------------*/ 
//used pins
#define JOYSTICK_Y    A0
#define JOYSTICK_X    A1
#define POTENTIOMETER A2
#define BUTTON        2

enum SERVO_CHANNEL {EYES_X = 0,         //#0
                    EYES_Y,             //#1
                    EYE_DX_LID_UP,      //#2
                    EYE_DX_LID_DOWN,    //#3
                    EYE_SX_LID_UP,      //#4
                    EYE_SX_LID_DOWN};   //#5

//Board 0: Address = 0x40 Offset = binary 00000 (no jumpers required)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); 

//eyes
int x, y;
int eyesX, eyesY;

//lid
int lidUpEyeDx, lidDownEyeDx;
int lidUpEyeSx, lidDownEyeSx;
int lidTrim   = 0;
int lidButton = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("start");

    pinMode(POTENTIOMETER, INPUT);
    pinMode(BUTTON, INPUT);
 
    pwm.begin();
    pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

    delay(10);
}

void loop() {

    //eyes position
    x = analogRead(JOYSTICK_X);
    y = analogRead(JOYSTICK_Y);
    eyesX = map(x, 0, 1023, 220, 440);  //converting from Degrees to pulse length
    eyesY = map(y, 0, 1023, 250, 500);

    //lid trim
    lidTrim = analogRead(POTENTIOMETER);
    lidTrim = map(lidTrim, 320, 580, -40, 40);

    lidUpEyeDx = map(y, 0, 1023, 400, 280);
    lidUpEyeDx -= (lidTrim - 40);
    lidUpEyeDx = constrain(lidUpEyeDx, 280, 400);
    lidUpEyeSx = 680 - lidUpEyeDx;

    lidDownEyeDx = map(y, 0, 1023, 410, 280);
    lidDownEyeDx += (lidTrim / 2);
    lidDownEyeDx = constrain(lidDownEyeDx, 280, 400);      
    lidDownEyeSx = 680 - lidDownEyeDx;
 
    //eyes
    pwm.setPWM(EYES_X, 0, eyesX);
    pwm.setPWM(EYES_Y, 0, eyesY);

    //lid
    lidButton = digitalRead(BUTTON);
    if (lidButton == HIGH) {
        pwm.setPWM(EYE_DX_LID_UP  , 0, 400);
        pwm.setPWM(EYE_DX_LID_DOWN, 0, 240);
        pwm.setPWM(EYE_SX_LID_UP  , 0, 240);
        pwm.setPWM(EYE_SX_LID_DOWN, 0, 400);
    }
    else if (lidButton == LOW) {
        pwm.setPWM(EYE_DX_LID_UP,   0, lidUpEyeDx);
        pwm.setPWM(EYE_DX_LID_DOWN, 0, lidDownEyeDx);
        pwm.setPWM(EYE_SX_LID_UP,   0, lidUpEyeSx);
        pwm.setPWM(EYE_SX_LID_DOWN, 0, lidDownEyeSx);
    }

    Serial.println(trim);
      
    delay(5);
}
