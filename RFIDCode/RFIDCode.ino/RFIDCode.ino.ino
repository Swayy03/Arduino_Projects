#include <SPI.h>
#include <MFRC522.h>
#include <Stepper.h>

int buzzPin = 2;
int greenPin = 7;
int redPin = 4;
int delayT = 200;
int delayT1 = 600;
int stepsPerRevolution = 2048;
int motSpeed = 10;
int count = 0;
int ForceOpen = 0;
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Stepper myStepper(stepsPerRevolution,8,5,3,6);
void setup() 
{
  myStepper.setSpeed(motSpeed);
  pinMode(greenPin,OUTPUT);
  pinMode(redPin,OUTPUT);
  pinMode(buzzPin,OUTPUT);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
//  Serial.println("Approximate your card to the reader...");
  Serial.println();
 //myStepper.step(-500);
 
  
 // myStepper.step(50);
}
void loop() 
{
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  
  if (content.substring(1) == "17 86 0F 3C" && count%2 == 1) //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Samson's Card Authorized access");
    Serial.println();
    digitalWrite(greenPin,HIGH);
    digitalWrite(redPin,HIGH);                                                                                                                              
    myStepper.step(850);
    myStepper.step(-300);
    delay(delayT1);
    digitalWrite(buzzPin,HIGH);
    delay(delayT1);
    digitalWrite(greenPin,HIGH);
    digitalWrite(redPin,LOW);
    digitalWrite(buzzPin,LOW);
    count++;
    
  
    
  }
  else if(content.substring(1) == "5B 10 63 1B" && count%2 == 0){
      digitalWrite(greenPin,HIGH);
      digitalWrite(redPin,HIGH);
      myStepper.step(-550);
      digitalWrite(greenPin,LOW);
      digitalWrite(buzzPin,HIGH);
      delay(delayT1);
      digitalWrite(buzzPin,LOW);
      count++;
  }

  
  else if(content.substring(1) == "17 86 0F 3C"){
    ForceOpen++;
    digitalWrite(redPin,HIGH);
    digitalWrite(buzzPin,HIGH);
    delay(delayT);
    digitalWrite(redPin,LOW);
    digitalWrite(buzzPin,LOW);
    delay(delayT);
    digitalWrite(greenPin,HIGH);
    digitalWrite(buzzPin,HIGH);
    delay(delayT);
    digitalWrite(greenPin,LOW);
    digitalWrite(buzzPin,LOW);
    delay(delayT);
    digitalWrite(redPin,HIGH);
    digitalWrite(buzzPin,HIGH);
    delay(delayT);
    digitalWrite(redPin,LOW);
    digitalWrite(buzzPin,LOW);
    delay(delayT);
    if(ForceOpen == 4){
        myStepper.step(2048);
      }
      if(ForceOpen == 5){
        myStepper.step(-2048);
        ForceOpen = 0;
      }
  }
  
  else 
  {
     Serial.println("Access denied");
    Serial.println();
    digitalWrite(redPin,HIGH);
    digitalWrite(buzzPin,HIGH);
    delay(delayT);
    digitalWrite(redPin,LOW);
    digitalWrite(buzzPin,LOW);
    delay(delayT);
    digitalWrite(redPin,HIGH);
    digitalWrite(buzzPin,HIGH);
    delay(delayT);
    digitalWrite(redPin,LOW);
    digitalWrite(buzzPin,LOW);
    delay(delayT);
    digitalWrite(redPin,HIGH);
    digitalWrite(buzzPin,HIGH);
    delay(delayT);
    digitalWrite(redPin,LOW);
    digitalWrite(buzzPin,LOW);
   
    //delay(3000);
    
  }
 
 
} 
