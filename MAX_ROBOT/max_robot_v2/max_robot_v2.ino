#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define shoulder 0
#define elbow 1
#define hand 2
#define claw 3
Adafruit_PWMServoDriver max = Adafruit_PWMServoDriver();

#define SERVOMIN 90
#define SERVOMAX 625
int shoulderDegrees;
int elbowDegrees;
int clawDegrees;

int shoulderpulselength;
int elbowpulselength;
int clawpulselength;
int valuex;
int valuey;
bool btn;

  


void setup() {
  Serial.begin(9600);
  max.begin();
  max.setPWMFreq(60);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(3, INPUT);
  
}


void loop() {
 valuex = analogRead(A0);
 valuey = analogRead(A1);
 btn = digitalRead(2);
 Serial.println(valuex);

  shoulderpulselength = map(valuex, 0, 1023, SERVOMIN, SERVOMAX);
  elbowpulselength = map(valuey, 0, 1023, SERVOMIN, SERVOMAX);
  max.setPWM(shoulder, 0, shoulderpulselength);
  max.setPWM(elbow, 0, elbowpulselength);
}
