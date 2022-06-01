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
# include <string.h>

// const uint16_t spr = 2048;
// const uint8_t stepperSpeed = 10;
// Stepper baseStepper (spr,8,10,9,11);

// const uint8_t foreArmServoPin = 2;
// const uint8_t upperArmServoPin = 3;
// Servo upperArmServo;
// Servo foreArmServo;

String reciveArduinoData;

void sendArduinoData(String data);

bool autoHome();
bool autoHomeStatus;

void setup()
{
  Serial.begin(115200);
  //Serial.setTimeout(10);
  // baseStepper.setSpeed(stepperSpeed);
  // upperArmServo.attach(upperArmServoPin);
  // foreArmServo.attach(foreArmServoPin);
  pinMode(13,OUTPUT);

}
void loop ()
{

  while(Serial.available() == 0)
  {
    // do nothing
  }

  reciveArduinoData = Serial.readStringUntil('\r');
  //char firstcharacter = reciveArduinoData[0];

    if (reciveArduinoData == "G10")
    {
      autoHomeStatus = autoHome();
        if (autoHomeStatus == true)
        {
          sendArduinoData("AUTO HOME COMPLET.");
        }
    }

  
  





}



bool autoHome()
{
  digitalWrite(13,HIGH);
  
  return true;
}
void sendArduinoData(String data)
{
  Serial.println(data);
}