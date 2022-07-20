# include <Arduino.h>
# include <LibPrintf.h>
# include <PID_v1.h>
# include <Servo.h>


int myPos = 90;
int dealyTime = 10;



const uint8_t endLimitPin1 = 2;
const uint8_t endlimitPin2 = 3;
const uint8_t feedbackPot = A0;
const uint8_t motorEnablePin = 6;
const uint8_t motorDirection1 = 5;
const uint8_t motorDirection2 = 4;

bool moveUpperArmServo(int servoPos);
bool moveForeArmServo(int servoPos);
bool launchUARM(int foreArm ,int upperArm , int base);

bool motorWritePos(int);

bool autoHome(void);
void autoHomeRight(void);
void autoHomeLeft(void);

void motorRevolveCW(bool spin,int speed);
void motorRevolveCCW(bool spin, int speed);
void endLimitOneAttained(void);
void endLimitTwoAttained(void);

double PidSetPoint = 0,PidInput = 0,PidOutput = 0;
double kp = .1331;
double ki = 0.1;
double kd = 0;

// double kp = .1331;
// double ki = 0.1;
// double kd = 0;


PID motorPID( &PidInput, &PidOutput, &PidSetPoint,kp,ki,kd,DIRECT);

volatile bool endlimit1trigger = false;
volatile bool endlimit2trigger = false;


int feedbackPotValue;
volatile int feedbackPotMaxAvrgVal;
int feedbackPotMax = 0;
volatile int feedbackPotMinAvrgVal;
int feedbackPotMin = 0;

int motorSpeedValue = 135;
int autoHomespeedValue = 120;

int autoHomeBasePos = 90;
int autoHomeForeArmPos = 110;
int autoHomeUpperArmPos = 100;

int prevUpperArmServoPos;
int upperArmServoPos;
int prevforeArmServoPos;
int foreArmServoPos;

int mapUSVal;

const uint8_t foreArmServoPin =13;
const uint8_t upperArmServoPin =12;
Servo upperArmServo;
Servo foreArmServo;


void setup()
{
  foreArmServo.write(175);
  upperArmServo.write(90);
  Serial.begin(9600);
  pinMode(endLimitPin1,INPUT);
  pinMode(endlimitPin2,INPUT);

  attachInterrupt(0,endLimitOneAttained,FALLING);
  attachInterrupt(1,endLimitTwoAttained,FALLING);

  pinMode(feedbackPot,INPUT);
  pinMode(motorEnablePin,OUTPUT);
  pinMode(motorDirection1,OUTPUT);
  pinMode(motorDirection2,OUTPUT);

  motorPID.SetMode(AUTOMATIC);
  motorPID.SetOutputLimits(-225,225);
  motorPID.SetSampleTime(1);

  foreArmServo.attach(foreArmServoPin);
  upperArmServo.attach(upperArmServoPin);


    autoHome();


    while(motorWritePos(myPos) == false) ;



}

void loop()
{
  
   while(launchUARM(110,100,90) == false);
   delay(100);
   while(motorWritePos(45) == false);
   delay(100);
   while(launchUARM(175,90,90) == false );
   delay (100);
   while(motorWritePos(135) == false);
   delay(100);

}

void endLimitOneAttained()
{
  endlimit1trigger = true;
  motorRevolveCW(false,0);
  feedbackPotMinAvrgVal = analogRead(feedbackPot);

}
void endLimitTwoAttained()
{
  endlimit2trigger = true;
  motorRevolveCCW(false,0);
  feedbackPotMaxAvrgVal = analogRead(feedbackPot);
 
}

bool autoHome()
{
  int feedbackval = analogRead(feedbackPot);
  
  if (feedbackval > 800)
  {
    motorRevolveCW(true,motorSpeedValue);
    delay(500);
    motorRevolveCW(false,0);

  }
  if (feedbackval < 368)
  {
    motorRevolveCCW(true,motorSpeedValue);
    delay(500);
    motorRevolveCCW(false,0);

  }

  if (feedbackval < 518)
  {
    autoHomeRight();
    autoHomeLeft();

  }
  else
  {
    autoHomeLeft();
    autoHomeRight();

  }
 
  return true;
}

void motorRevolveCW(bool spin ,int speed)
{
  if (spin == true )
  {
    motorRevolveCCW(false,0);
    analogWrite(motorEnablePin,speed);
    digitalWrite(motorDirection1,HIGH);
  }
  else
  {
    analogWrite(motorEnablePin,speed);
    digitalWrite(motorDirection1,LOW);
  }

}

void motorRevolveCCW(bool spin ,int speed)
{
  if (spin  == true )
  {
    motorRevolveCW(false,0);
    analogWrite(motorEnablePin,speed);
    digitalWrite(motorDirection2,HIGH);
  }
  else
  {
    analogWrite(motorEnablePin,speed);
    digitalWrite(motorDirection2,LOW);
  }

}

void autoHomeRight(void)
{
  delay(10);
  motorRevolveCW(true,motorSpeedValue);
    
    while(endlimit1trigger == false)
    {
      motorRevolveCW(true,motorSpeedValue);
      Serial.println("waiting for endlimit1 to reach");
    }

    int avrgA = feedbackPotMinAvrgVal;
    endlimit1trigger = false;
    motorRevolveCCW(true,autoHomespeedValue);
    delay(500);
    motorRevolveCW(true,autoHomespeedValue);

    while(endlimit1trigger == false)
    {
      Serial.println("waitng for endlimit1 to reach second time");
    }
    
    int avrgB = feedbackPotMinAvrgVal;
    endlimit1trigger = false;
    feedbackPotMin = (avrgA + avrgB);
    feedbackPotMin = feedbackPotMin/2;
    Serial.println(feedbackPotMax);
    Serial.println(feedbackPotMin);

    return;
}

void autoHomeLeft(void)
{
  delay(10);
  motorRevolveCCW(true,motorSpeedValue);

  while(endlimit2trigger == false)
  {
    motorRevolveCCW(true,motorSpeedValue);

    Serial.println("waiting for the endlimit2 to reach first time");
  }

  int avrgA = feedbackPotMaxAvrgVal;
  endlimit2trigger = false;

  motorRevolveCW(true,autoHomespeedValue);
  delay(500);
  motorRevolveCCW(true,autoHomespeedValue);

  while(endlimit2trigger == false)
  {
    Serial.println("waiting for the endlimit2 to reach second time");
  }

  int avrgB = feedbackPotMaxAvrgVal;
  endlimit2trigger = false;
  feedbackPotMax = (avrgA + avrgB);
  feedbackPotMax = feedbackPotMax/2;
  Serial.println(feedbackPotMax);
  Serial.println(feedbackPotMin);

  return;
}

bool motorWritePos(int position)
{
  feedbackPotValue = analogRead(feedbackPot);
  PidInput = map(feedbackPotValue,feedbackPotMin,feedbackPotMax,0,180);
  PidSetPoint = position;
  motorPID.Compute();
  printf("Feedback pot : %i Pid set point : %lf Pid input : %lf Pid output : %lf\n",feedbackPotValue,PidSetPoint,PidInput,PidOutput);

  delay(100);
  


  if (PidOutput > 0 )
  {
    motorRevolveCCW(true,motorSpeedValue); 
  }

  if (PidOutput > 0 && PidOutput < 3.5)
  {
    motorRevolveCCW(false,0);
    motorRevolveCW(false,0);
    return true;

  }
  if (PidOutput > - 4 && PidOutput < 0)
  {
    motorRevolveCCW(false,0);
    motorRevolveCW(false,0);
    return true;

  }
  
  if (PidOutput < 0)
  {
    motorRevolveCW(true,motorSpeedValue);

  }

  if (PidOutput > - 5 && PidOutput < 0)
  {
    motorRevolveCCW(false,0);
    motorRevolveCW(false,0);
    return true;

  }

  delay(50);
 return false;
}


bool launchUARM(int foreArm ,int upperArm , int base)
{
  prevforeArmServoPos = foreArmServo.read();
  prevUpperArmServoPos = upperArmServo.read();

   if (prevforeArmServoPos == foreArm && prevUpperArmServoPos == upperArm)
   {
    return true;
   }

  if (foreArmServo.read() > foreArm)
  {
    prevforeArmServoPos = prevforeArmServoPos - 1;
    foreArmServo.write(prevforeArmServoPos);
    delay(dealyTime);
  }

  if (upperArmServo.read() > upperArm)
  {
    prevUpperArmServoPos = prevUpperArmServoPos - 1;
    upperArmServo.write(prevUpperArmServoPos);
    delay(dealyTime);
    
  }

  if (foreArmServo.read() < foreArm)
  {
    prevforeArmServoPos = prevforeArmServoPos + 1;
    foreArmServo.write(prevforeArmServoPos);
    delay(dealyTime);
    
  }

    if (upperArmServo.read() < upperArm)
  {
    prevUpperArmServoPos = prevUpperArmServoPos + 1;
    upperArmServo.write(prevUpperArmServoPos);
    delay(dealyTime);
    
  }

  

  Serial.print(foreArmServo.read());
  Serial.print("\t");
  Serial.println(upperArmServo.read());

  return false;



}


