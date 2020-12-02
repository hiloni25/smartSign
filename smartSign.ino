#include "SevSeg.h"
#include <SoftwareSerial.h>

SevSeg sevseg;
SoftwareSerial BT(A4,A3);

float displayTimeSecs = 1; //how long do you want each number on display to show (in secs)
float displayTime = (displayTimeSecs * 5000);
long buzzerFrequency = 200;
float buzzerDuration = (displayTimeSecs * 100);
//long startNumber = 20; //countdown starts with this number
long endNumber = 0; //countdown ends with this number
String state;
long startNumber = 0;

const int buzzerPin = A0;
const int trigPin = A1;
const int echoPin = A2; 
 
long duration;
int distance;
int safetyDistance;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin,OUTPUT);
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
  
  bool resistorsOnSegments = false;
  byte hardwareConfig = COMMON_CATHODE; 
  bool updateWithDelays = false;
  bool leadingZeros = true;
  bool disableDecPoint = true;
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(100);
  Serial.begin(9600);
  BT.begin(9600);
  Serial.begin(9600);
  
}

void loop() {

  while(BT.available()){

  delay(10);
  char c = BT.read();
  state += c;
  Serial.println(state);
  //startNumber = long(state); 
  char* behind;
  startNumber = strtol(state.c_str(), &behind, 10);
  Serial.println(startNumber); }
  
  if (startNumber >= endNumber) {
    for (long i = 0; i <= displayTime; i++){
      sevseg.setNumber(startNumber,0);
      sevseg.refreshDisplay(); 
    } 
  startNumber--;

  //tone(buzzerPin,buzzerFrequency,buzzerDuration);
  digitalWrite(trigPin, LOW); //Clears the trigPin
  delayMicroseconds(2);

  //Sets the trigPin on HIGH State for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  //Calculating disance
  distance = duration*0.034/2; //gives me distance in cm

  safetyDistance = distance;  
  Serial.println(safetyDistance); 
  
  if(safetyDistance <= 100){  
     
    //tone(buzzerPin,buzzerFrequency,buzzerDuration);
    //tone(buzzerPin,10000,20);         
    digitalWrite(buzzerPin, HIGH);   
    //digitalWrite(ledPin, HIGH);
  }
  else if(safetyDistance <= 15){
    //digitalWrite(buzzerPin, HIGH); 
    //tone(buzzerPin,buzzerFrequency,buzzerDuration); 
    tone(buzzerPin,10,2);  
  }
  else{
      digitalWrite(buzzerPin, LOW);
      //digitalWrite(ledPin, LOW);
    
  }
  
  //tone(buzzerPin,buzzerFrequency,buzzerDuration);    
  //sevseg.blank();
  //}
  }
  
//sevseg.setNumber(0000,0); //after countdown shows endNumber, show this number. 
sevseg.blank();
sevseg.refreshDisplay();
} 
