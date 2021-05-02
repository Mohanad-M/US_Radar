# 1 "C:\\Users\\engin\\OneDrive\\Desktop\\US_Radar\\ArduinoCode\\US_Radar_ARDUINO\\US_Radar_ARDUINO.ino"
/*----------------------------------------------------------------------------------------

%%  US_Radar_ARDUINO.ino

% _Ver.:      1.0.0

% _Author:    Mohanad M. Marzouk

% _Date:      210503_Initial

% _Last Mod.: 210503

% _Brief:

%   __ Arduino code for ultrasonic radar project

-----------------------------------------------------------------------------------------*/
# 10 "C:\\Users\\engin\\OneDrive\\Desktop\\US_Radar\\ArduinoCode\\US_Radar_ARDUINO\\US_Radar_ARDUINO.ino"
# 11 "C:\\Users\\engin\\OneDrive\\Desktop\\US_Radar\\ArduinoCode\\US_Radar_ARDUINO\\US_Radar_ARDUINO.ino" 2
Servo MyServo;

/* Public constants */





/* Global public variables */
int distance;
int degree;

/* function setup */
void setup()
{
  Serial.begin(9600); /* start serial com with 9600 baudrate */
  MyServo.attach(2); /* declare servo motor PIN as output */
  pinMode(6 /* Echo PIN */,0x0); /* declare US sensor Echo pin as input */
  pinMode(7 /* trigger PIN */,0x1); /* declare US sensor trigger pin as output */
  pinMode(9 /* PIN for red LED */,0x1); /* declare Red LED pin as output */
  pinMode(8 /* PIN for green LED */,0x1); /* declare Green LED pin as output */
  delay(100); /* delay 100 ms for the setup function to load */
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
  digitalWrite(7 /* trigger PIN */,0x0);
  delayMicroseconds(2);
  digitalWrite(7 /* trigger PIN */,0x1);
  delayMicroseconds(10);
  long time = pulseIn(6 /* Echo PIN */,0x1);
  distance = time/28.5/2;

  if(distance > 100){
    distance = 100;
  }

  if(distance > 50){
    digitalWrite(8 /* PIN for green LED */,0x1);
    digitalWrite(9 /* PIN for red LED */,0x0);
  }
  else{
    digitalWrite(8 /* PIN for green LED */,0x0);
    digitalWrite(9 /* PIN for red LED */,0x1);
  }

  Serial.print(degree);
  Serial.print(" ");
  Serial.println(distance);
}
