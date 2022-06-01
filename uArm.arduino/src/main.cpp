/* 
 *  src code 4 uArm
 *    main.cpp
 * 
 *  Created on: 2022-May-26
 *        Dev : segin
 * 
 *  Ongoing-devlopment
 * 
 *  GNU General Public License v3.0 
 */

# include <Arduino.h>
# include <Stepper.h>
# include <Servo.h>

const uint16_t spr = 2048;
const uint8_t stepperSpeed = 10;
Stepper baseStepper (spr,8,10,9,11);

const uint8_t foreArmServoPin = 2;
const uint8_t upperArmServoPin = 3;
Servo upperArmServo;
Servo foreArmServo;


void setup()
{
  Serial.begin(9600);
  baseStepper.setSpeed(stepperSpeed);
  upperArmServo.attach(upperArmServoPin);
  foreArmServo.attach(foreArmServoPin);

}
void loop ()
{
   
}

int autoHome ()
{
  
}