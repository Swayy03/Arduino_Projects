#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#define shoulder 0
#define elbow 1
#define hand 2
#define claw 3
Adafruit_PWMServoDriver max = Adafruit_PWMServoDriver();
Adafruit_MPU6050 mpu;
#define SERVOMIN 90
#define SERVOMAX 625
int shoulderDegrees;
int elbowDegrees;
int clawDegrees;

int shoulderpulselength;
int elbowpulselength;
int clawpulselength;
int shoulderposition = SERVOMIN;
int elbowposition = SERVOMIN;
int valuex;
int valuey;
bool btn;
int motionValue;

void Rest(){
  max.setPWM(shoulder, 0, SERVOMIN);
  max.setPWM(elbow, 0, SERVOMIN);
}

  


void setup() {
  Serial.begin(115200);
  //while(!Serial){
    //delay(10);
  //}
  max.begin();
  if(!mpu.begin()){
    Serial.println("Couldn't find motion sensor");
    while(1){
      delay(10);
    }
  }
  Serial.println("Found Motion sensor.....MAX AWAKENS....");
  max.setPWMFreq(60);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(3, INPUT);
  pinMode(5,OUTPUT);
  digitalWrite(5, HIGH);
  Rest();
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
  
}


void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  \
  
  if(a.acceleration.x>0 && motionValue != a.acceleration.x && elbowposition < SERVOMAX){
    elbowposition += 8;
    max.setPWM(elbow, 0, elbowposition);
  }
  if(a.acceleration.x<0 && motionValue != a.acceleration.x && elbowposition > SERVOMIN){
    elbowposition -= 8;
    max.setPWM(elbow, 0, elbowposition);
  }
  motionValue = a.acceleration.x;

/*
 valuex = analogRead(A0);
 valuey = analogRead(A1);
 btn = digitalRead(3);
 Serial.print("X: ");
 Serial.print(valuex);
 Serial.print("     Y: ");
 Serial.print(valuey);
 Serial.print("    Button: ");
 Serial.println(btn);

 if(valuey >510 && elbowposition < SERVOMAX){
  elbowposition = elbowposition+8; 
  max.setPWM(elbow, 0, elbowposition);
 }
 else if (valuey <490 && elbowposition > SERVOMIN){
  elbowposition = elbowposition - 8;
  max.setPWM(elbow, 0, elbowposition);
 }
//######SHOUDLER   ######################
 if(valuex >520 && shoulderposition < SERVOMAX){
  shoulderposition = shoulderposition+8; 
  max.setPWM(shoulder, 0, shoulderposition);
 }
 else if (valuex <490 && shoulderposition > SERVOMIN){
  shoulderposition = shoulderposition - 8;
  max.setPWM(shoulder, 0, shoulderposition);
 }
 */



  
}
