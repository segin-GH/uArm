# include <Arduino.h>
# include <Servo.h>

Servo servoZero;
int servoZeroPin = 2;
Servo servoOne;
int servoOnePin = 3;

void setup()
{
  Serial.begin(9600);
  servoZero.attach(servoZeroPin);
  servoOne.attach(servoOnePin);
}

void loop()
{
  servoZero.write(70);
  servoOne.write(90);
}
