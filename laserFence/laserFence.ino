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
// Inputs
const int LaserPointer = 0; // PD0 OUTPUT 
const int AlarmLamp = 1;    // PD1 OUTPUT  
const int GreenLED = 2;     // PD2 OUTPUT
const int RedLED = 3;       // PD3 OUTPUT
const int RunMode = 4;      // PD4 INPUT - High when in setup, low when in run
const int Buzzer = 5;       // PD5 OUTPUT
const int LaserArm = 6;     // PD6 INPUT - Goes low when armed

const int LaserDetect = 0;  // PC0 INPUT Laser detector


void sendMorse(const char msg);

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
        sendMorse('L');
      }
      if(digitalRead(RunMode)==false){
        sendMorse('M');
      }
      alerted=true;
      time=millis()+3000; // How long to wait before repeating warnings
    }
    
    // Check for timeout
    if(time>millis()){
      alerted=false;
    }
  }
}

void loop()
{
  if(digitalRead(LaserArm)){
    // Laser live, check setup 
  }
}

void sendMorse(const char msg)
{
  // TO DO
}
