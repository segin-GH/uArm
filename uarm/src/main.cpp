# include <Arduino.h>
# include <Servo.h>              
# include<Stepper.h>

int spr = 2048;
const uint8_t mot_speed = 16;

Servo servo_griper;
Servo servo_upperArm;
Servo servo_forArm;
Stepper stepper_base (spr,8,10,9,11);


int servo_upperArm_degree = 90;
int servo_forArm_degree = 90;
int servo_gripper_degree = 90;
int stepper_base_degree;

void setup()
{
  Serial.begin(9600);
  servo_upperArm.attach(2);
  servo_forArm.attach(3);
  servo_griper.attach(4);
  stepper_base.setSpeed(mot_speed);

}

void loop()
{
  //
}