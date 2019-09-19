#include <Servo.h> 
#include <stdlib.h>

int sensorPins[] = {A0,A1};   // select the analog input pin for the photoresistor
char *lightString[] = {"Right ", "Left "};

int bottomSensorPins[] = {A2,A3};   // select the analog input pin for the photoresistor
char *bottomLightString[] = {"Front ", "Back "};

const int servoPin1 = 12; 
const int servoPin2 = 13;

int ultraSoundSignalPins[] = {9,10,11}; // Front Right, Center, Front Left
char *pingString[] = {"Front Right ","Center ", "Front Left "}; // just something to print to indicate direction
int counter = 0;
int bottomCounter = 0;

//Servo Names
Servo Servo1; // Right
Servo Servo2; // Left 

void setup() { 
   Servo1.attach(servoPin1); 
   Servo2.attach(servoPin2); 
   Serial.begin(9600);
   delay(2000);
}

void loop() {
 pingControl();
  if(checkBottomLight()==true);
    int bottomCounter = 1;
  if ((counter==0)&&(bottomCounter==0)){
    if (blackTape()==true){
      reverse();
      turnRight();
     }
  }
  if (checkLight()==true){
    int counter = 1;
  }
 else forward();
  pingControl();
  if (checkLight() == true)lightControl(); 
  else forward();
  
}

void pingControl(){
  ping();
  if (leftPing()== true)turnRight();   
  else if (rightPing()== true)turnLeft();
  else if (centerPing()== true) {
    reverse();
    delay(500);
    turnRight();
    delay(2000);
  }
  else forward();
}

//Ping Commands
int pingVals[3];
void ping() {
  for (int i=0; i<3; i++) {
    unsigned long echo;

    pinMode(ultraSoundSignalPins[i], OUTPUT); // Switch signalpin to output
    digitalWrite(ultraSoundSignalPins[i], LOW); // Send low pulse
//    delayMicroseconds(2); // Wait for 2 microseconds
    digitalWrite(ultraSoundSignalPins[i], HIGH); // Send high pulse
//    delayMicroseconds(5); // Wait for 5 microseconds
    digitalWrite(ultraSoundSignalPins[i], LOW); // Holdoff
    pinMode(ultraSoundSignalPins[i], INPUT); // Switch signalpin to input
    digitalWrite(ultraSoundSignalPins[i], HIGH); // Turn on pullup resistor
    echo = pulseIn(ultraSoundSignalPins[i], HIGH); //Listen for echo
    pingVals[i]= (echo / 58.138) * .39; //convert to CM then to inches
   }
}

//Left Ping Check
bool leftPing() {
  if (pingVals[2] <= 8) return true;
  else return false;    
}

  //Right Ping Check
bool rightPing() {
  if (pingVals[0] <= 8) return true;
  else return false;
}

  //Center Ping Check
bool centerPing () {
  if (pingVals[1] <= 8) return true;
  else return false;
}

void lightControl(){
   light();
   if (rightStronger()==true){
    turnRight();
    forward();
   }
   
   else if (leftSronger()==true){
    turnLeft();
    forward();
   }
   else forward();
}

int sensors[2];
int light() {  
  for(int i=0; i < 2; i++)
  {
     Serial.println(lightString[i]);
     Serial.println(analogRead(sensorPins[i]));
     delay(1000); 
  }
  sensors[0] = analogRead(sensorPins[0]);
  sensors[1] = analogRead(sensorPins[1]);
}

bool rightStronger(){
  if ((sensors[0]>sensors[1])&&(abs(sensors[0]-sensors[1])>=100)) return true;
  
  else return false;
}

bool leftSronger(){
  if ((sensors[0]<sensors[1])&&(abs(sensors[0]-sensors[1])>=100))return true;
  else return false;
}

bool checkLight(){
  light();
  if ((sensors[0]&&sensors[1])>200)return true;
}

int bottomSensors[2];
int bottomLight() {  
  for(int i=0; i < 2; i++)
  {
     Serial.println(bottomLightString[i]);
     Serial.println(analogRead(bottomSensorPins[i]));
     delay(500); 
  }
  bottomSensors[0] = analogRead(bottomSensorPins[0]);
  bottomSensors[1] = analogRead(bottomSensorPins[1]);
}

bool blackTape(){
  if (abs(bottomSensors[0]-bottomSensors[1])<315) return true;
  else return false;
}

bool checkBottomLight(){
  bottomLight();
  if((bottomSensors[0]&&bottomSensors[1])<100)return true;
}


void forward() {
   Servo1.writeMicroseconds(1300);
   Servo2.writeMicroseconds(1305);
   delay(1000);
}
void turnRight() {
  Servo1.writeMicroseconds(1685);
  Servo2.writeMicroseconds(1315);
  delay(1000);
}
void turnLeft() {
  Servo1.writeMicroseconds(1300);
  Servo2.writeMicroseconds(1700);
  delay(1000);
}
void stopCar() {
   Servo1.writeMicroseconds(1480);
   Servo2.writeMicroseconds(1485);
   Servo2.writeMicroseconds(1495);
}
void reverse() {
  Servo1.writeMicroseconds(1645);
  Servo2.writeMicroseconds(1650);
  delay(1000);
}
