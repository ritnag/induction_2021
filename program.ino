#include <servo.h>
//IR sensor
int IRL = 1;
int IRL = 2;
int IRL = 3;
//Ultrasonic sensor
#define eco1 4;
#define trig1 5;
#define eco2 6;
#define trig2 7;
//Wheels Motors
int motorl1 = 8;
int motorl2 = 9;
int motorr1 = 10;
int motorr2 = 11;
//Servo Motors

//Real Time Clock

//
void setup() 
{
  
}

void loop() 
{
  
}
void linefollower() //line follower
{
  
}
void RFID() //Patent Identification
{
  #include <SPI.h>
  #include <MFRC522.h>
 
  #define SS_PIN 10
  #define RST_PIN 9
  MFRC522 mfrc522(SS_PIN, RST_PIN);   
 
void setup() 
{
  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();  
  Serial.println("Approximate your card to the reader...");       //doubt
  Serial.println();

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
  byte letter;                                                          //??
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));                             //doubt
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "BD 31 15 2B")                        //change here the UID of the card that you want to give access to
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
} 

}


void Ultrasonic() //object detection
{
  
  #define echoPin 2 
  #define trigPin 3 


long duration; 
int distance; 

void setup()
{
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600);
  Serial.println("Ultrasonic Sensor HC-SR04 Test");             //statement required to be printed?
  Serial.println("with Arduino UNO R3");
}
void loop()
{
  digitalWrite(trigPin, LOW);
  delay(2000);
  digitalWrite(trigPin, HIGH);
  delay(10000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 

  Serial.print("Distance: ");
  Serial.print(distance);  
  Serial.println(" cm");                                 //will it come in next line
}
}


  
}
void medicines() //Despensing system
{#include<Servo.h>
Servo motor;
int p=9;        //digital pin connected
void setup()
{
motor.attach(9);
motor.write(180);
}
void loop()
{
 for(p=0;p<180;p++)
{
motor.write(p);
delay(10);
}
for(p=180;p>=1;p--)
{
motor.write(p);
delay(10);
}
}

  
}
void irsensor() //despensing gate way
{
  void setup() 
{

  pinMode (IRSensor, INPUT); 
  pinMode (LED, OUTPUT); 
}

void loop()
{
  int statusSensor = digitalRead (IRSensor);
  
  if (statusSensor == 1)
    digitalWrite(LED, LOW); 
}
  
  else
  {
    digitalWrite(LED, HIGH); 
  }
  
}

  

void time()
{#include<Wire.h>
#include<Time.h>
#include<DS1307RTC.h>
void setup(){
Serial.begin(9600);
while(!serial);
delay(200);
}
void loop(){
void time()
}
void time() {
int time; 
tmElements_t tm;
time=RTC.read(tm);
returntime;
}

  
}
void Soundsystem()
{
  
}

}
//
