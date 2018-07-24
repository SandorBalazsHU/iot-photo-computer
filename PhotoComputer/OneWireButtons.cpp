#include <Arduino.h>
#include "OneWireButtons.h"

OneWireButtons::OneWireButtons(int inputPin) : inputPin(inputPin)
{

}

int OneWireButtons::checkButtons()
{
  this->inputValue = analogRead(this->inputPin);
  for(int i = 0; i<this->buttonsNumber; i++)
  {
    if(this->callibrationLimits[i][0]<=this->inputValue && this->callibrationLimits[i][1]>=this->inputValue)
    {
      return i;
    }
  }
  return 0;
}
