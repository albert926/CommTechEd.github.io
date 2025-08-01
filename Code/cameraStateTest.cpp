/*
This will use the builtinled to test if the huskylens is working.
*/

#include <Arduino.h>
//you have to install this library for the project
#include <HUSKYLENS.h>

//make sure these pin constants are correct!
const uint8_t BuiltInLed = 0;

bool seeBallFlag = 0;

//setup the Husklens object
HUSKYLENS huskylens;


void setup()
{
  pinMode(BuiltInLed, OUTPUT);
  Wire.begin();
  
  //flash LED if huskylens doesn't begin
  while(!huskylens.begin(Wire))
  {
    digitalWrite(BuiltInLed, HIGH);
    delay(200);
    digitalWrite(BuiltInLed, LOW);
    delay(200);
  }

}

void loop()
{
  //set seeBallFlag by seeing if husklens sees a block with ID of 1
  huskylens.requestBlocks(1);
  if(huskylens.available())
  {
    seeBallFlag = 1;
  }
  else
  {
    //this may dim the light if your program is reading faster than camera can read
    //clearing the seeBallFlag may not be necessary for your final program until after it attempts to score a goal.
    seeBallFlag = 0;
  }

  //turn on LED if camera sees the ball
  digitalWrite(BuiltInLed, seeBallFlag);
}
