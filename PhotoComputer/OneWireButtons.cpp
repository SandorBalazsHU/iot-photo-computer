#include <Arduino.h>
#include "OneWireButtons.h"

OneWireButtons::OneWireButtons(int inputPin) : inputPin(inputPin)
{

}

int OneWireButtons::checkButtons()
{
  this->inputValue = analogRead(this->inputPin);
  return 0;
}
