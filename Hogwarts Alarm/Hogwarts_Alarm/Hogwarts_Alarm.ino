int voltPin = A1;
int buzzPin = 8;
int greenPin = 4;
int redPin = 7;
int readVal;
int dtc1 = 430;
int dtc2 = 480;
int dtc3 = 570;
int dtc4 = 470;
int dtc5 = 620;
int dtc6 = 860;
int dtc7 = 650;
int dtc8 = 550;
int dtc9 = 590;
int dtc10 = 650;
int dtc11 = 700;
int dtc12 = 570;
int dtc13 = 850;

void Hogwarts_Alarm(){
  for(int i=0;i<=220;i++){
 digitalWrite(buzzPin,HIGH);
 delayMicroseconds(dtc6);
 digitalWrite(buzzPin,LOW);
 delayMicroseconds(dtc6);
 }
 delay(30);

 for(int i=0;i<=540;i++){
 digitalWrite(buzzPin,HIGH);
 delayMicroseconds(dtc7);
 digitalWrite(buzzPin,LOW);
 delayMicroseconds(dtc7);
 }
delay(10);

 for(int i=0;i<=200;i++){
 digitalWrite(buzzPin,HIGH);
 delayMicroseconds(dtc8);
 digitalWrite(buzzPin,LOW);
 delayMicroseconds(dtc8);
 }
 

 for(int i=0;i<=300;i++){
 digitalWrite(buzzPin,HIGH);
 delayMicroseconds(dtc9);
 digitalWrite(buzzPin,LOW);
 delayMicroseconds(dtc9);
 }


for(int i=0;i<=600;i++){
 digitalWrite(buzzPin,HIGH);
 delayMicroseconds(dtc10);
 digitalWrite(buzzPin,LOW);
 delayMicroseconds(dtc10);
 }
 
  
 for(int i=0;i<=640;i++){
 digitalWrite(buzzPin,HIGH);
 delayMicroseconds(dtc1);
 digitalWrite(buzzPin,LOW);
 delayMicroseconds(dtc1);
 }

  
 for(int i=0;i<=1100;i++){
 digitalWrite(buzzPin,HIGH);
 delayMicroseconds(dtc2);
 digitalWrite(buzzPin,LOW);
 delayMicroseconds(dtc2);
 }
 
 
 for(int i=0;i<=890;i++){
 digitalWrite(buzzPin,HIGH);
 delayMicroseconds(dtc3);
 digitalWrite(buzzPin,LOW);
 delayMicroseconds(dtc3);
 }

 
 for(int i=0;i<=500;i++){
 digitalWrite(buzzPin,HIGH);
 delayMicroseconds(dtc7);
 digitalWrite(buzzPin,LOW);
 delayMicroseconds(dtc7);
 }

 for(int i=0;i<=200;i++){
 digitalWrite(buzzPin,HIGH);
 delayMicroseconds(dtc8);
 digitalWrite(buzzPin,LOW);
 delayMicroseconds(dtc8);
 }
 

 for(int i=0;i<=200;i++){
 digitalWrite(buzzPin,HIGH);
 delayMicroseconds(dtc9);
 digitalWrite(buzzPin,LOW);
 delayMicroseconds(dtc9);
 }


for(int i=0;i<=550;i++){
 digitalWrite(buzzPin,HIGH);
 delayMicroseconds(dtc11);
 digitalWrite(buzzPin,LOW);
 delayMicroseconds(dtc11);
 }
 for(int i=0;i<=400;i++){
 digitalWrite(buzzPin,HIGH);
 delayMicroseconds(dtc12);
 digitalWrite(buzzPin,LOW);
 delayMicroseconds(dtc12);
 }


for(int i=0;i<=550;i++){
 digitalWrite(buzzPin,HIGH);
 delayMicroseconds(dtc13);
 digitalWrite(buzzPin,LOW);
 delayMicroseconds(dtc13);
 }
 delay(1000);
}


void setup() {
 Serial.begin(9600);
 pinMode(voltPin,INPUT);
 pinMode(greenPin,OUTPUT);
 pinMode(redPin,OUTPUT);
 pinMode(buzzPin,OUTPUT);

}

void loop() {
  readVal = analogRead(voltPin);
  Serial.println(readVal);
  if(readVal >=70){
    digitalWrite(greenPin,HIGH);
    digitalWrite(redPin,LOW);
   Hogwarts_Alarm();
  }
  else
    digitalWrite(redPin,HIGH);
    digitalWrite(greenPin,LOW);
}
