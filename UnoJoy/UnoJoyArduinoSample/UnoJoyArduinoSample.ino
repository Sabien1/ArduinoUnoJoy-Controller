
#include "UnoJoy.h"
#include "Encoder.h"

int sim = 0;
bool ctDwn = false;
Encoder myEnc(2,3);
long newPosition = 128;
void setup(){
  setupPins();
  setupUnoJoy();
}

void loop(){
  // Always be getting fresh data
  newPosition = myEnc.read() + 128;
  dataForController_t controllerData = getControllerData();
  setControllerData(controllerData);
}

void setupPins(void){
  // Set all the digital pins as inputs
  // with the pull-up enabled, except for the 
  // two serial line pins
  for (int i = 2; i <= 12; i++){
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }
  pinMode(A4, INPUT);
  digitalWrite(A4, HIGH);
  pinMode(A5, INPUT);
  digitalWrite(A5, HIGH);
}

dataForController_t getControllerData(void){
  
  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  dataForController_t controllerData = getBlankDataForController();
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins
  controllerData.triangleOn = LOW;
  controllerData.circleOn = LOW;
  controllerData.squareOn = LOW;
  controllerData.crossOn = LOW;
  controllerData.dpadUpOn = LOW;
  controllerData.dpadDownOn = LOW;
  controllerData.dpadLeftOn = LOW;
  controllerData.dpadRightOn = LOW;
  controllerData.l1On = LOW;
  controllerData.r1On = LOW;
  controllerData.selectOn = LOW;
  controllerData.startOn = LOW;
  controllerData.homeOn = LOW;
  
  // Set the analog sticks
  //  Since analogRead(pin) returns a 10 bit value,
  //  we need to perform a bit shift operation to
  //  lose the 2 least significant bits and get an
  //  8 bit number that we can use 
     // MODIFIED  -  For rotary encoder, this should read from digital pins 2 and 3.
     // block puts a stop on the rotary input in the event of input larger than the appropriate HID value
     if (newPosition < 0)
     {
         controllerData.leftStickX = 0;
     }
     else if (newPosition > 255)
     {
         controllerData.leftStickX = 255; 
     }
     else
     {
         controllerData.leftStickX = newPosition; 
     }
     
     
     // Test block ------------------------------------------
   /*if (!ctDwn && sim < 255)
   { 
      controllerData.leftStickX = sim++;
   }
   else
   {
      ctDwn = true;
   }
   if (ctDwn && sim > 0)
   {
    controllerData.leftStickX = sim--;
   }
   else
   {
      ctDwn = false;
   }*/ // End Test Block
   // analogRead(A0) >> 2;
  controllerData.leftStickY = 128;
  controllerData.rightStickX = 128;
  controllerData.rightStickY = 128;
  // And return the data!
  //delay(1);
  return controllerData;
}
