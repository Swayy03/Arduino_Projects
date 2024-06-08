#include <AFMotor.h>
#include<NewPing.h>
#include <Servo.h>
#include <Wire.h>
AF_DCMotor BackLeft(1);
AF_DCMotor BackRight(2);
AF_DCMotor FrontRight(3);
AF_DCMotor FrontLeft(4);
#define MAX_DISTANCE 200
#define MAX_SPEED 255
#define MAX_SPEED_OFFSET 25
#define echoPin A2                           // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
#define trigPin A1         
NewPing sonar(trigPin,echoPin,400);                 // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
long duration, distance;
int position;
float distance2 = sonar.ping_cm();

Servo servo1;


//Robot Functions
void roboStop(){
  BackLeft.run(RELEASE);
  BackRight.run(RELEASE);
  FrontLeft.run(RELEASE);
  FrontRight.run(RELEASE);
  delay(1000);
}
void roboStopBrief(){
  BackLeft.run(RELEASE);
  BackRight.run(RELEASE);
  FrontLeft.run(RELEASE);
  FrontRight.run(RELEASE);
  delay(50);
}
void roboForward(){
  //roboStopBrief();
  BackLeft.run(FORWARD);
  BackRight.run(FORWARD);
  FrontLeft.run(FORWARD);
  FrontRight.run(FORWARD);
}
void roboReverse(){
  roboStopBrief();
  BackLeft.run(BACKWARD);
  BackRight.run(BACKWARD);
  FrontLeft.run(BACKWARD);
  FrontRight.run(BACKWARD);
  delay(700);
}
void roboTurnRight(){
  roboStopBrief();
  BackRight.run(BACKWARD);
  FrontRight.run(BACKWARD);
  delay(200);
  BackLeft.run(FORWARD);
  FrontLeft.run(FORWARD);
  delay(200);
}
void roboTurnLeft(){
  roboStopBrief();
  BackLeft.run(BACKWARD);
  FrontLeft.run(BACKWARD);
  delay(200);
  BackRight.run(FORWARD);
  FrontRight.run(FORWARD);
  delay(200);
}
bool roboSearchLeft(){
  for(position = 180;position>=90;position--){
    servo1.write(position);
    delay(10);
    distance2 = sonar.ping_cm();
    Serial.println(distance2);
    if(distance2 > 20){
      servo1.write(90);
      roboTurnLeft();
      return 1;
    }
  }
  return 0;
}
bool roboSearchRight(){
  for(position = 0;position<=90;position++){
    servo1.write(position);
    delay(10);
    distance2 = sonar.ping_cm();
    Serial.println(distance2);
    if(distance2 > 20){
      servo1.write(90);
      roboTurnRight();
      return 1;
    }
  }
  return 0;
}


void setup(){
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo1.attach(10);
  BackLeft.setSpeed(255);
  BackRight.setSpeed(255);
  FrontLeft.setSpeed(255);
  FrontRight.setSpeed(255);

  BackLeft.run(RELEASE);
  BackRight.run(RELEASE);
  FrontLeft.run(RELEASE);
  FrontRight.run(RELEASE);

  servo1.write(90);
  delay(2000);
}
void loop(){

  //Set the ultrasonic sensor to send pulses in 10ms intervals
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //calculate the distance between the ultrasonic sensor and an obstacle
  distance2 = sonar.ping_cm();

  //if the distance is decreasing and has reached 20--stop and search for a route
  //Stop->searchLeft(if no way)->searchRight(if there is no way...meaning robot is completely obstructed)->move back and look for a route
  if(distance2 <= 20 &&distance2 != 0){
    roboStop();
    if(!roboSearchLeft()){
      roboStop();
      if(!roboSearchRight()){
        roboStop();
        roboReverse();
      }
    }
    
  }
  //if the distance is over 20->Move forward
  else{
    roboForward();
  }

}
