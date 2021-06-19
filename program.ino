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
int motorr2 = 11;ahdbcj
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

}
void Ultrasonic() //object detection
{
  
}
void medicines() //Despensing system
{#include<Servo.h>
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
  
}
void Soundsystem()
{
  
}

}
//
