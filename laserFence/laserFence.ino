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
  
  unsigned long time=millis();
  
  // Ensure that the laser is not armed on powerup
  while(digitalRead(LaserArm)){
    
    // Set red led only
    digitalWrite(RedLED,HIGH);
    digitalWrite(GreenLED,LOW);
    
    // Check to see if timeout has expired
    if(millis()>time+2500){
      digitalWrite(AlarmLamp,HIGH); // Put the lamp on
      sendMorse('W'); // Warning!
      time=millis();
    }
    
    // And sleep 
    delay(500); 
  }
}

void loop()
{
  //
}

void sendMorse(const char msg)
{
  // TO DO
}
