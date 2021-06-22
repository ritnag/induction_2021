#include <servo.h>
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <SPI.h>
#include <MFRC522.h>
//#include <ESPS8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include "RTClib.h"


// #define FIREBASE_HOST ""
// #define FIREBASE_AUTH""
// #define WIFI_SSID""
// #define WIFI_PASSWORD""
String myString;
char rdata;
int adata = 0;

int irstVal;







//IR sensor
//int IRL = A0;
//int IRL = A1;
int IRH = 2;
int IRO = 3;

//Ultrasonic sensor
// #define eco1 4;
// #define trig1 5;
// #define eco2 6;
// #define trig2 7;

//Line Follower 
#define in1 9
#define in2 8
#define in3 7
#define in4 6
#define enA 10
#define enB 5
int M1_Speed = 100; // speed of motor 
int M2_Speed = 100; // speed of motor 2
int LeftRotationSpeed = 250;  // Left Rotation Speed
int RightRotationSpeed = 250; // Right Rotation Speed
  
//Servo Motors

//Real Time Clock
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};


//Buzzer
int buz 12;

//LED
int Rled 13;
int Gled 14;

//IOT
SoftwareSerial mySerial(2, 3); // RX, TX

//RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN); 

//=========================================================================   VOID SETUP   ==============================================================================================

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
  //  while (!Serial); // for Leonardo/Micro/Zero
  Serial.begin(9600);
  if (! rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning())
  {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  } 


  
  //RFID  
  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();  
  Serial.println("Approximate your card to the reader...");       //doubt
  Serial.println();


  
  //IR Sensor
  pinMode (IRH, INPUT); // sensor pin INPUT
  
  //Ultrasonic Sensor
//  pinMode(trig1, OUTPUT); 
//  pinMode(eco1, INPUT); 
//  pinMode(trig2, OUTPUT); 
//  pinMode(eco2, INPUT); 
//  Serial.begin(9600);
//  Serial.println("Ultrasonic Sensor HC-SR04 Test");             //statement required to be printed?
//  Serial.println("with Arduino UNO R3");
//  


  //Servo Motors
  
  //Stepper Motor
   
  //Buzzer
  digitalWrite(buz, OUTPUT);
  
  //LED
  digitalWrite(Rled, OUTPUT);
  digitalWrite(Gled, OUTPUT);
  
  
  //
  
  pinMode(LED_BUILTIN, OUTPUT);                            // EXAMPLE ONE
 delay(3000);
 Serial.begin(115200);
 Serial.println();
 Serial.print("Configuring access point...");
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
 server.on ( "/", handleRoot );
 server.on ("/save", handleSave);
 server.begin();
 Serial.println ( "HTTP server started" );
 server.on("/LED_BUILTIN_on", []() {
   digitalWrite(LED_BUILTIN, 1);
   Serial.println("on");
   handleRoot();
 });
 server.on("/LED_BUILTIN_off", []() {
   digitalWrite(LED_BUILTIN, 0);
   Serial.println("off");
   handleRoot();
 });
}
void loop() {
 server.handleClient();
}


//========================================================================  VOID LOOP  =================================================================================================

void loop() 
{
  linefollower();
}


//=================================================================   LINE FOLLOWER FUNCTION   =================================================================================================


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
   right();
   delay(5000);
   stop();
   despensing(); // despensing or RIFD have to read RFID and choose
   delay(10000);
   left();
   delay(5000);
   stop();
   forward();
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




//=======================================================================   RFID ANTENNA   ============================================================================


void RFID() //Patent Identification
{ 
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
    byte letter;         //??
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
       Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       Serial.print(mfrc522.uid.uidByte[i], HEX);
       content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       content.concat(String(mfrc522.uid.uidByte[i], HEX));      //doubt
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    if (content.substring(1) == "BD 31 15 2B")  //change here the UID of the card that you want to give access to
    {
      Serial.println("Authorized access");
      Serial.println();
      delay(3000);
    }
   
   else
   {
      Serial.println(" Access denied");
      delay(3000);
    }
  } 
}


//==================================================================  DESPENSING   ======================================================================================================



void despensing() //Despensing system
{
  Servo motor;
  int p=9;        //digital pin connected
  void setup()
  {
    motor.attach(9);
    motor.write(180);
  }
  
    int statusSensor = digitalRead(IRSensor); // reads the IR sensor input
  
  if (statusSensor == 0)
     despensing();
  
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

void motor1()
{

}

void motor2()
{

}

void motor3()
{

}

void motor4()//main dispeinsing
{

}
}
  
  
  
//====================================================================   IR SENSOR   ====================================================================================================

void irsensor() //despensing gate way
{
  int statusSensor = digitalRead(IRSensor); // reads the IR sensor input
  
  if (statusSensor == 0)
     despensing();
}


//======================================================================  RTC   ==================================================================================================

void time()
{
  DateTime now = rtc.now();
  int date_time[5]={now.day(), now.month(), now.year(), now.hour(), now.minute()};
  Serial.print(date_time);
//  Serial.print(now.year(), DEC);
//  Serial.print('/');
//  Serial.print(now.month(), DEC);
//  Serial.print('/');
//  Serial.print(now.day(), DEC);
//  Serial.print(" (");
//  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]); // if required to print the day of the week
//  Serial.print(") ");
//  Serial.print(now.hour(), DEC);
//  Serial.print(':');
//  Serial.print(now.minute(), DEC);
//  Serial.print(':');
//  Serial.print(now.second(), DEC);
//  Serial.println();

//  Serial.print(" since midnight 1/1/1970 = ");
//  Serial.print(now.unixtime());
//  Serial.print("s = ");
//  Serial.print(now.unixtime() / 86400L);
//  Serial.println("d");

  // calculate a date which is 7 days and 30 seconds into the future
//  DateTime future (now + TimeSpan(7, 12, 30, 6));
//
//  Serial.print(" now + 7d + 30s: ");
//  Serial.print(future.year(), DEC);
//  Serial.print('/');
//  Serial.print(future.month(), DEC);
//  Serial.print('/');
//  Serial.print(future.day(), DEC);
//  Serial.print(' ');
//  Serial.print(future.hour(), DEC);
//  Serial.print(':');
//  Serial.print(future.minute(), DEC);
//  Serial.print(':');
//  Serial.print(future.second(), DEC);
//  Serial.println();

//  Serial.println();
  delay(3000);
}



//=======================================================================  BUZZER  =================================================================================================

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
  
//  server.handleClient();                    // EXAMPLE  ONE
}

 

//==============================================================   SERIAL COMMUNICATION   ==========================================================================================================

void connection()
{
// SoftwareSerial mySerial(2, 3); // RX, TX
// void setup()
// {  
//   Serial.begin(115200);
//   while (!Serial)
//   {
//     ;    // wait for serial port to connect. Needed for Native USB only
//   }
//   Serial.println("Goodnight moon!");                 //d
//   // set the data rate for the SoftwareSerial port
//   mySerial.begin(38400);
//   mySerial.println("Hello, world?");              //
// }
// void loop() 
// {
  if (mySerial.available())
    Serial.write(mySerial.read());                      
  if (Serial.available())
    mySerial.write(Serial.read());
}
