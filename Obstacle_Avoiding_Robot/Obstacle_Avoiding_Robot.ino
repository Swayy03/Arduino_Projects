#include<AFMotor.h>
#include<NewPing.h>
#include <Servo.h>
AF_DCMotor BackLeft(1);
AF_DCMotor BackRight(2);
AF_DCMotor FrontRight(3);
AF_DCMotor FrontLeft(4);
#define MAX_DISTANCE 200
#define MAX_SPEED 255
#define MAX_SPEED_OFFSET 25
#define Trig A0
#define Echo A1
NewPing sonar(Trig,Echo,400);
int duration = 0;
int distance = 0;
int left;
int right;
int L = 0;
int R = 0;
int position = 0;
Servo servo1;


             void  roboForward(){
                                
                                 BackLeft.run(FORWARD);
                                 BackRight.run(BACKWARD);
                                 FrontLeft.run(BACKWARD);
                                 FrontRight.run(FORWARD);
                                 Serial.print("The thing is :");
                                 Serial.println(sonar.ping_cm());
                                 
                                 }
             void roboStop(){
                            BackLeft.run(RELEASE);
                            BackRight.run(RELEASE);
                            FrontLeft.run(RELEASE);
                            FrontRight.run(RELEASE);
                            delay(1000);
                            }
             void roboTurnRight(){
                             roboStop();
                             FrontLeft.run(BACKWARD);
                             BackLeft.run(FORWARD);
                             FrontRight.run(RELEASE);
                             BackRight.run(RELEASE);
                            
                             delay(500);
                             FrontRight.run(BACKWARD);
                             BackRight.run(FORWARD);
                              FrontLeft.run(RELEASE);
                             BackLeft.run(RELEASE);
                             delay(500);
                             if(sonar.ping_cm()>=20){
                               roboStop();
                             }

                            }   
            void roboTurnLeft(){
                            roboStop();
                             FrontLeft.run(FORWARD);
                             BackLeft.run(BACKWARD);
                             FrontRight.run(RELEASE);
                             BackRight.run(RELEASE);
                            
                             delay(500);
                             FrontRight.run(FORWARD);
                             BackRight.run(BACKWARD);
                              FrontLeft.run(RELEASE);
                             BackLeft.run(RELEASE);
                             delay(500);
                            }



void setup() {
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  servo1.attach(10);
  BackLeft.setSpeed(255);
  BackRight.setSpeed(255);
  FrontLeft.setSpeed(255);
  FrontRight.setSpeed(255);

  BackLeft.run(RELEASE);
  BackRight.run(RELEASE);
  FrontLeft.run(RELEASE);
  FrontRight.run(RELEASE);
  Serial.begin(9600);
  delay(20);

  servo1.write(90);
  delay(5000);


}

void loop() {
  digitalWrite(Trig,HIGH);
  delayMicroseconds(1000);
  digitalWrite(Trig,LOW);


 
 
  if(sonar.ping_cm()<20){
    roboStop();
       for(position=0;position<=90;position++){
         servo1.write(position);
         delay(10);
         if (sonar.ping_cm()>=20){
           servo1.write(90);
           roboTurnRight();
           break;
         }
         else if(position==90){
           break;
         }
       }
       for(position=90;position<=180;position++){
         servo1.write(position);
         delay(10);
         if (sonar.ping_cm()>=20){
           servo1.write(90);
           roboTurnLeft();
           break;
         }
         else if(position==180){
           break;
         }
       }


       for(position=180;position>=90;position--){
         servo1.write(position);
         delay(10);
         if (sonar.ping_cm()>=20){
           servo1.write(90);
           roboTurnLeft();
           break;
         }
         else if(position==90){
           break;
         }
       }


      for(position=90;position>=0;position--){
         servo1.write(position);
         delay(10);
         if (sonar.ping_cm()>=20){
           servo1.write(90);
           roboTurnRight();
           break;
         }

       }
  }
   /* for(position = 0;position<=180;position++){
      servo1.write(position);
      delay(10);
       if(sonar.ping_cm() >= 20){
         servo1.write(90);
         roboTurnLeft();
         break;
       }
       else if(position ==0){
         break;
                            }
    }
    for(position = 180;position>=0;position--){
       servo1.write(position);
      delay(10);
      
       if(sonar.ping_cm() >= 20){
         servo1.write(90);
         roboTurnLeft();
         break;
       }
       else if(position ==0){
         break;
                            }
        
    
  }

  }
*/
  else if(sonar.ping_cm()>=20 && sonar.ping_cm()<100){
    servo1.write(90);
    roboForward();
    delay(100);
  }
  else if(sonar.ping_cm()>=100&&sonar.ping_cm()<=400){
    roboForward();
  }
  
}

