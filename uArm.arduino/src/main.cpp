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
# include <Servo.h>
# include <string.h>


// const uint8_t foreArmServoPin = 2;
// const uint8_t upperArmServoPin = 3;
// Servo upperArmServo;
// Servo foreArmServo;

String recivedPythonData;

void sendToPython(String data);
String reciveFromPython();

bool autoHome();
bool autoHomeStatus;

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(10);
  // upperArmServo.attach(upperArmServoPin)
  // foreArmServo.attach(foreArmServoPin);

}
void loop ()
{

  while(Serial.available() == 0)
  {
    // do nothing
  }

  recivedPythonData = reciveFromPython();
  char firstCharacter = recivedPythonData[0];
  char secondCharacter = recivedPythonData[1];
  char thirdCharacter = recivedPythonData[2];

    if (firstCharacter == 'G')
    {
      autoHomeStatus = autoHome();
      
      if (autoHomeStatus == true)
      {
        sendToPython(" AUTOHOME COMPLET");
      }
    }
    if (firstCharacter == 'M' && secondCharacter == '2')
    {
      // do something
    }
    if(firstCharacter == 'M' && secondCharacter == '3')
    {
      // do something
    }

  

}



bool autoHome()
{
  digitalWrite(13,HIGH);
  delay(1000);
  
  return true;
}
void sendToPython(String data)
{
  Serial.println(data);
}

String reciveFromPython()
{
  recivedPythonData = Serial.readStringUntil('\r');
  return recivedPythonData;

}