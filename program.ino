#include <servo.h>
#include<Wire.h>
#include<Time.h>
#include<DS1307RTC.h>
#include <SPI.h>
#include <MFRC522.h>

//IR sensor
//int IRL = A0;
//int IRL = A1;
int IRL = 3;

//Ultrasonic sensor
#define eco1 4;
#define trig1 5;
#define eco2 6;
#define trig2 7;

//Wheels Motors
#define in1 9
#define in2 8
#define in3 7
#define in4 6
#define enA 10
#define enB 5
int M1_Speed = 80; // speed of motor 
int M2_Speed = 80; // speed of motor 2
int LeftRotationSpeed = 250;  // Left Rotation Speed
int RightRotationSpeed = 250; // Right Rotation Speed
  
//Servo Motors

//Real Time Clock

//Buzzer
int buz 12;

//LED
int Rled 13;
int Gled 14;

void setup() 
{
  //Line FOllower  
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(A0, INPUT); // initialize Left sensor as an input
  pinMode(A1, INPUT); // initialize Right sensor as an input
        
  //RTC
  Serial.begin(9600);
  while(!serial);
  delay(200);
  
  //RFID  
  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();  
  Serial.println("Approximate your card to the reader...");       //doubt
  Serial.println();
  
  //IR Sensor

  
  //Ultrasonic Sensor
  pinMode(trig1, OUTPUT); 
  pinMode(eco1, INPUT); 
  pinMode(trig2, OUTPUT); 
  pinMode(eco2, INPUT); 
  Serial.begin(9600);
  Serial.println("Ultrasonic Sensor HC-SR04 Test");             //statement required to be printed?
  Serial.println("with Arduino UNO R3");
  
  //Servo Motors
  
  //Stepper Motor
  
  //Buzzer
  digitalWrite(buz, OUTPUT);
  
  //LED
  digitalWrite(Rled, OUTPUT);
  digitalWrite(Gled, OUTPUT);
  //
  
}

void loop() 
{
  linefollower();
}


void linefollower() //line follower
{
  int LEFT_SENSOR = digitalRead(A0);
  int RIGHT_SENSOR = digitalRead(A1);
  if(RIGHT_SENSOR==0 && LEFT_SENSOR==0) 
  {
    forward(); //FORWARD
  }
  else if(RIGHT_SENSOR==0 && LEFT_SENSOR==1) 
  {
    right(); //Move Right
  }
  else if(RIGHT_SENSOR==1 && LEFT_SENSOR==0) 
  {
    left(); //Move Left
  }
  else if(RIGHT_SENSOR==1 && LEFT_SENSOR==1) 
  {
   Stop();  //STOP
  }
}  
 
void forward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}
void backward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, M1_Speed);
  analogWrite(enB, M2_Speed);
}
void right()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}
void left()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, LeftRotationSpeed);
  analogWrite(enB, RightRotationSpeed);
}
void Stop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void RFID() //Patent Identification
{ 
  #define SS_PIN 10
  #define RST_PIN 9
  MFRC522 mfrc522(SS_PIN, RST_PIN);   

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
  long duration; 
  int distance; 
  digitalWrite(trig1, LOW);
  digitalWrite(trig2, LOW);
  delay(2000);
  digitalWrite(trig1, HIGH);
  
  delay(10000);
  digitalWrite(trig1, LOW);
  digitalWrite(trig2, LOW);
  duration = pulseIn(eco1, HIGH);
  
  distance = duration * 0.034 / 2; 

  Serial.print("Distance: ");
  Serial.print(distance);  
  Serial.println(" cm");        //will it come in next line
}

void medicines() //Despensing system
{
  Servo motor;
int p=9;        //digital pin connected
void setup(){
motor.attach(9);
motor.write(180);
}
void loop(){
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
  
}
void time()
{
void setup(){

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
void buzzReady()
{
  digitalWrite(buz, HIGH);
  delay(2000);
  digitalWrite(buz, LOW);
  delay(2000);
  digitalWrite(buz, HIGH);
  delay(2000);
  digitalWrite(buz, LOW);  
}
void buzzDone()
{
  digitalWrite(buz, HIGH);
  delay(1000);
  digitalWrite(buz, LOW);
  delay(1000);
  digitalWrite(buz, HIGH);
  delay(1000);
  digitalWrite(buz, LOW);
}
