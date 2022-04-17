# include <Arduino.h>
# include <Servo.h>              
# include<Stepper.h>

  int spr = 2048;
  const uint8_t mot_speed = 16;

  Servo servo_griper;
  Servo servo_upperArm;
  Servo servo_foreArm;
  Stepper stepper_base (spr,8,10,9,11);


  int servo_upperArm_degree = 90;
  int servo_foreArm_degree = 90;
  int servo_gripper_degree = 90;
  int stepper_base_degree;

  const uint8_t left_joystick_x = A0;
  const uint8_t left_joystick_y = A1;
  const uint8_t right_joystick_x = A2;
  const uint8_t right_joystick_y = A3;


void setup()
{
  Serial.begin(9600);
  servo_upperArm.attach(2);
  servo_foreArm.attach(3);
  servo_griper.attach(4);
  stepper_base.setSpeed(mot_speed);

  pinMode(left_joystick_x,INPUT);
  pinMode(left_joystick_y,INPUT);
  pinMode(right_joystick_x,INPUT);
  pinMode(right_joystick_y,INPUT);


}

void loop()
{
  int left_joystick_x_value = analogRead(left_joystick_x);
  int left_joystick_y_value = analogRead(left_joystick_y);
  int right_joystick_x_value = analogRead(right_joystick_x);
  int right_joystick_y_value = analogRead(right_joystick_y);

    // **********************Left Joystick Logic*******************************

  if (left_joystick_x_value < 350)
  {
    servo_upperArm_degree = servo_upperArm_degree - 7;
  }
  else if (left_joystick_x_value > 680)
  {
    servo_upperArm_degree = servo_upperArm_degree + 7;
  }


  if (left_joystick_y_value < 350)
  {
    stepper_base.step(-1);
  }
  else if (left_joystick_y_value > 680)
  {
    stepper_base.step(+1);
  }

    // ************************Right Joystick Logic*******************************

  if (right_joystick_x_value < 350)
  {
    servo_foreArm_degree = servo_foreArm_degree - 7;
  }
  else if (right_joystick_x_value > 680)
  {
    servo_foreArm_degree = servo_foreArm_degree + 7;
  }
     // **************************** End Limts Logic *******************************

  

}