/* 
 A laser fence detection system 
 Copyright Neil Stoker 2012
 Licenced under the GPL v3 (or later)  http://www.gnu.org/licenses/gpl.txt
 
 CIRCUIT
 Inputs
 PD6 covered switch to activte laser
 PD4 pushbutton to control RunMode (either setup or run)
 PC0 phototransistor to detect laser beam
 
 Outputs
 PD0 laser pointer *CAUTION NEEDED*
 PD1 security alarm lamp - flashes at 2Hz
 PD2 Green section of bi-colour led
 PD3 Red section of bi-colour led
 PD5 BuzzerDriver
 
 */

#include "Morse.h"

// Inputs
const int LaserPointer = 0; // PD0 OUTPUT 
const int AlarmLamp = 1;    // PD1 OUTPUT  
const int GreenLED = 2;     // PD2 OUTPUT
const int RedLED = 3;       // PD3 OUTPUT
const int RunMode = 4;      // PD4 INPUT - High when in setup, low when in run
const int Buzzer = 5;       // PD5 OUTPUT
const int LaserArm = 6;     // PD6 INPUT - Goes low when armed

const int LaserDetector = 0;  // PC0 INPUT Laser detector


Morse morse(Buzzer,12,0);  // Params Pin, speed, 0 = toggle

bool laserLive = false;  
bool alerted = false;
unsigned long long backgroundLight;

void setLED(bool green, bool red)
{
  digitalWrite(GreenLED, green);
  digitalWrite(RedLED, red);
}

void calibrateDetector(void){
  unsigned long long totalReadings=0;
  for(int i=0;i<100;i++){
    totalReadings+=analogRead(LaserDetector);
    delay(100);
  }
  backgroundLight=totalReadings/100;
}

bool beamDetected(void){
  return (analogRead(LaserDetector)>backgroundLight);
}


void setup()
{
  // Initialise the ports to input/outputs and check laser not armed before proceeding

  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,INPUT);

  // Detection of the standing light values moved to the pre-arm warning of the laser

  unsigned long time=0;

  bool safetyCheck=true;    // Flag to warn of setup errors - false if safe to continue
  bool alerted=false; // Flag to repeat alarm

  // Ensure that the laser is not armed on powerup, and RunMode setup
  while(safetyCheck){
    safetyCheck = digitalRead(LaserArm) || digitalRead(RunMode);

    // Set red led only
    digitalWrite(AlarmLamp,HIGH); // Put the lamp on
    digitalWrite(RedLED,HIGH);
    digitalWrite(GreenLED,LOW);

    // Sound the alerts
    if(!alerted) {
      if(digitalRead(LaserArm)==false){
        morse.send('L');
      }
      if(digitalRead(RunMode)==false){
        morse.send('M');
      }
      alerted=true;
      time=millis()+3000; // How long to wait before repeating warnings
    }

    // Check for timeout
    if(time>millis()){
      alerted=false;
    }
  }

  alerted=false;
}

void loop()
{
  if(digitalRead(LaserArm)){
    if(!alerted) {
      // Need to calibrate the light settings
      morse.send('CAL');
      calibrateDetector();
      morse.send('RUN');
      alerted = true;
    } 
    else    if(digitalRead(RunMode)) {
      // High so in setup mode
      bool targetted=beamDetected();
      setLED(targetted,true);
      digitalWrite(AlarmLamp,targetted);
    } 
    else {
      // RunMode is low, so we're playing for real
    } 
  }
  else {
    // Laser not armed, ensure green light and laser off
    digitalWrite(LaserArm,LOW);
    digitalWrite(AlarmLamp,LOW);
    setLED(true,false); // Set green lamp
  }
}





