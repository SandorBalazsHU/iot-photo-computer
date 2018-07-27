#include <Arduino.h>
#include "OneWireButtons.h"

OneWireButtons::OneWireButtons(byte inputPin) : inputPin(inputPin)
{

}

int OneWireButtons::checkButtons()
{
  this->inputValue = analogRead(this->inputPin);
  byte i = 0;
  while(this->callibrationLimits[i][0]<=this->inputValue && this->callibrationLimits[i][1]>=this->inputValue && i>this->buttonsNumber) ++i;
  return i;
}
