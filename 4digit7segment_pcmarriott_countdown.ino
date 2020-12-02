#include "SevSeg.h"
SevSeg sevseg;

float displayTimeSecs = 1; //how long do you want each number on display to show (in secs)
float displayTime = (displayTimeSecs * 5000);
long buzzerFrequency = 500;
float buzzerDuration = (displayTimeSecs * 100);
long startNumber = 10; //countdown starts with this number
long endNumber = 0; //countdown ends with this number

const int buzzerPin = 0;

void setup() {
  pinMode(buzzerPin,OUTPUT);
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};
  
  bool resistorsOnSegments = false;
  byte hardwareConfig = COMMON_ANODE;
  bool updateWithDelays = false;
  bool leadingZeros = true;
  bool disableDecPoint = true;
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
}

void loop() {
  
  tone(buzzerPin,buzzerFrequency,buzzerDuration);
  
  if (startNumber >= endNumber) {
    for (long i = 0; i <= displayTime; i++){
      sevseg.setNumber(startNumber,0);
      sevseg.refreshDisplay();
    } 
  startNumber--;
  tone(buzzerPin,buzzerFrequency,buzzerDuration);    
  }
  
sevseg.setNumber(1234,0); //after countdown shows endNumber, show this number.
sevseg.refreshDisplay();
}
