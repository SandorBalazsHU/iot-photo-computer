#include <Arduino.h>
#include "OneWireButtons.h"

OneWireButtons::OneWireButtons(byte inputPin) : inputPin(inputPin)
{

}

byte OneWireButtons::checkButtons()
{
  this->inputValue = analogRead(this->inputPin);
  byte buttonValue = 0;
  
  for(byte i = 0; i<this->buttonsNumber; i++)
  {
    if(this->callibrationLimits[i][0] < this->inputValue && this->inputValue < this->callibrationLimits[i][1])
    {
      buttonValue = i+1;
      break;
    }
  }

  return buttonValue;
}

int OneWireButtons::callibrationCheck()
{
  return this->inputValue = analogRead(this->inputPin);
}
