int ledPin = 8;
int readPin = 12;
int readVal;
int delayT = 100;
int toggle = 1;



void setup() {
 pinMode(readPin,INPUT);
 pinMode(ledPin,OUTPUT);
Serial.begin(9600);
}

void loop() {

  readVal = digitalRead(readPin);
  Serial.println(readVal);
  delay(delayT);
  if(readVal == 0){
    toggle++;
  }
  if(toggle%2 == 0){
    digitalWrite(ledPin,HIGH);
    delay(delayT);
  }
  else if(toggle%2 !=0){
    digitalWrite(ledPin,LOW);
    delay(delayT);
  }
}
