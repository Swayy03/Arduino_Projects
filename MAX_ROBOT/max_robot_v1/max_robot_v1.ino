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
int x;
int chooseOperation;

  


void setup() {
  Serial.begin(9600);
  max.begin();
  max.setPWMFreq(60);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  x = 0;
  def(x);
}

void pickup(bool x){
  if(x == 1){
    shoulderDegrees = 40;
    elbowDegrees = 60;
    clawDegrees = 150;
    clawpulselength = map(clawDegrees, 0, 180, SERVOMIN, SERVOMAX);

    max.setPWM(claw, 0, clawpulselength);

    for(int i = 0;i<=shoulderDegrees-20;i++){
      shoulderpulselength = map(i, 0, 180, SERVOMIN, SERVOMAX);
      max.setPWM(0, 0, shoulderpulselength);
      delay(20);
    }
    shoulderpulselength = map(shoulderDegrees, 0, 180, SERVOMIN, SERVOMAX);
    max.setPWM(0, 0, shoulderpulselength);

    for(int j = 0;j<=elbowDegrees;j++){
      elbowpulselength = map(j, 0, 180, SERVOMIN, SERVOMAX);
      max.setPWM(1, 0, elbowpulselength);
      delay(10);
    }
    
    
    Serial.println("Picking up");
    delay(2000);
    x = 2;
    
  }
  else{
    Serial.println("Not picking up");
  }
}

void lift(){
  shoulderDegrees = 100;
  elbowDegrees = 60;
  clawDegrees = 15;

  shoulderpulselength = map(shoulderDegrees, 0, 180, SERVOMIN, SERVOMAX);
  elbowpulselength = map(elbowDegrees, 0, 180, SERVOMIN, SERVOMAX);
  clawpulselength = map(clawDegrees, 0, 180, SERVOMIN, SERVOMAX);

  max.setPWM(shoulder, 0, shoulderpulselength);
  max.setPWM(elbow, 0, elbowpulselength);
  max.setPWM(claw, 0, clawpulselength);
  Serial.println("Lifting");
  delay(2000);
}
void drop(){
  shoulderDegrees = 160;
  elbowDegrees = 110;
  clawDegrees = 75;

  shoulderpulselength = map(shoulderDegrees, 0, 180, SERVOMIN, SERVOMAX);
  elbowpulselength = map(elbowDegrees, 0, 180, SERVOMIN, SERVOMAX);
  clawpulselength = map(clawDegrees, 0, 180, SERVOMIN, SERVOMAX);

  max.setPWM(shoulder, 0, shoulderpulselength);
  max.setPWM(elbow, 0, elbowpulselength);
  Serial.println("Dropping");
  delay(2000);
  max.setPWM(claw, 0, clawpulselength);
  delay(2000);
}
void def(int x){
  if(x == 0){
    shoulderDegrees = 0;
    elbowDegrees = 30;
    clawDegrees = 0;

    shoulderpulselength = map(shoulderDegrees, 0, 180, SERVOMIN, SERVOMAX);
    elbowpulselength = map(elbowDegrees, 0, 180, SERVOMIN, SERVOMAX);
    clawpulselength = map(clawDegrees, 0, 180, SERVOMIN, SERVOMAX);

    for(int i = 0;i<=shoulderDegrees;i++){
      shoulderpulselength = map(i, 0, 180, SERVOMIN, SERVOMAX);
      max.setPWM(0, 0, shoulderpulselength);
      delay(10);
    }
    shoulderpulselength = map(shoulderDegrees, 0, 180, SERVOMIN, SERVOMAX);
    max.setPWM(0, 0, shoulderpulselength);

    for(int j = 0;j<=elbowDegrees;j++){
      elbowpulselength = map(j, 0, 180, SERVOMIN, SERVOMAX);
      max.setPWM(1, 0, elbowpulselength);
      delay(10);
    }
    

    
  }
  else if(x == 2){
    //shoulderDegrees = 0;
    elbowDegrees = 30;
    clawDegrees = 0;
    for(int j = elbowDegrees;j>=30;j--){
      elbowpulselength = map(j, 0, 180, SERVOMIN, SERVOMAX);
      max.setPWM(elbow, 0, elbowpulselength);
      delay(10);
    }
    for(int i=shoulderDegrees;i>=0;i--){
      shoulderpulselength = map(i, 0, 180, SERVOMIN, SERVOMAX);
      max.setPWM(shoulder, 0, shoulderpulselength);
      delay(10);
    }
    
    clawpulselength = map(clawDegrees, 0, 180, SERVOMIN, SERVOMAX);
    max.setPWM(claw, 0, clawpulselength);
  }
  else{
    Serial.println("Not defaulting");
  }
}

void loop() {

  Serial.println(x);
  Serial.println(shoulderpulselength);
  Serial.println(shoulderDegrees);

  
  while(Serial.available() == 0){}
  chooseOperation = Serial.parseInt();

  if(chooseOperation == 1){
    Serial.println("ChooseOperation pickup....");
    x = 1;
    pickup(x);
  }
  if(chooseOperation == 5){
    Serial.println("ChooseOperation drop....");
    drop();
  }
  if(chooseOperation == 2){
    Serial.println("ChooseOperation defaulting....");
    x = 2;
    def(x);
  }
  
  
  
  
}
