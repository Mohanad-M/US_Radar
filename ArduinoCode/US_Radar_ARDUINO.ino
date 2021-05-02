/*----------------------------------------------------------------------------------------
%%  US_Radar_ARDUINO.ino
% _Ver.:      1.0.0
% _Author:    Mohanad M. Marzouk
% _Date:      210503_Initial
% _Last Mod.: 210503
% _Brief:
%   __ Arduino code for ultrasonic radar project
-----------------------------------------------------------------------------------------*/
#include <Servo.h>
Servo MyServo;

/* Public constants */
#define ECHO  6   /* Echo PIN */
#define TRIG  7   /* trigger PIN */
#define G_LED 8   /* PIN for green LED */
#define R_LED 9   /* PIN for red LED */

/* Global public variables */
int distance;
int degree;

/* function setup */
void setup()
{
  Serial.begin(9600);     /* start serial com with 9600 baudrate */
  MyServo.attach(2);      /* declare servo motor PIN as output */
  pinMode(ECHO,INPUT);    /* declare US sensor Echo pin as input */
  pinMode(TRIG,OUTPUT);   /* declare US sensor trigger pin as output */
  pinMode(R_LED,OUTPUT);  /* declare Red LED pin as output */
  pinMode(G_LED,OUTPUT);  /* declare Green LED pin as output */
  delay(100);             /* delay 100 ms for the setup function to load */
}

/* function main */
void loop()
{
  for(degree = 1; degree < 180; degree++){
    MyServo.write(degree);
    delay(80);
    data();
  }

  for(degree = 180; degree > 1; degree--){
    MyServo.write(degree);
    delay(80);
    data();
  }
}

/* function data */
void data()
{
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  long time = pulseIn(ECHO,HIGH);
  distance = time/28.5/2;

  if(distance > 100){
    distance = 100;
  }
  
  if(distance > 50){
    digitalWrite(G_LED,HIGH);
    digitalWrite(R_LED,LOW);
  }
  else{
    digitalWrite(G_LED,LOW);
    digitalWrite(R_LED,HIGH);
  }

  Serial.print(degree);
  Serial.print(" ");
  Serial.println(distance);
}
