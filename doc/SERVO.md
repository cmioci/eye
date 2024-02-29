## Calibrating your servos

Servo pulse timing varies between different brands and models.  Since it is an analog control circuit, there is often some variation between samples of the same brand and model.  For precise position control, you will want to calibrate the minumum and maximum pulse-widths in your code to match known positions of the servo.

### Find the minimum
Using the example code, edit SERVOMIN until the low-point of the sweep reaches the minimum range of travel.  It is best to approach this gradually and stop before the physical limit of travel is reached.

### Find the maximum
Again using the example code, edit SERVOMAX until the high-point of the sweep reaches the maximum range of travel.  Again, is best to approach this gradually and stop before the physical limit of travel is reached.

### CAUTION !!!
Use caution when adjusting SERVOMIN and SERVOMAX. Hitting the physical limits of travel can strip the gears and permanently damage your servo.

## Converting from degrees to pulse length

The Arduino *map()* function is an easy way to convert between degrees of rotation and your calibrated SERVOMIN and SERVOMAX pulse lengths.  Assuming a typical servo with 180 degrees of rotation; once you have calibrated SERVOMIN to the 0-degree position and SERVOMAX to the 180 degree position, you can convert any angle between 0 and 180 degrees to the corresponding pulse length with the following line of code:

``` bash
pulselength = map(degrees, 0, 180, SERVOMIN, SERVOMAX);
```
