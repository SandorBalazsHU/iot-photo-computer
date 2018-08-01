#include <Arduino.h>
#include "Camera.h"

Camera::Camera(byte expoPin, byte focusPin) : expoPin(expoPin), focusPin(focusPin)
{
    this->startTime = 0;
    this->currentTime = 0;
    this->startSemafor = 0;
}
void Camera::setup()
{
    pinMode(this->expoPin, OUTPUT);
    pinMode(this->focusPin, OUTPUT);
}
byte Camera::focus(byte time)
{
    if(this->startSemafor == 0)
    {
        this->startTime = millis();
        this->startSemafor = 1;
        digitalWrite(this->focusPin, HIGH);
    }

    this->currentTime = millis();

    if(this->currentTime - this->startTime >= time )
    {
        digitalWrite(this->focusPin, LOW);
        return 1;
    }
    else
    {
        return 0;
    }
}
void Camera::exposition(byte time)
{

}
void Camera::singleExpo()
{
    digitalWrite(this->shootPin, HIGH);
    digitalWrite(this->focusPin, HIGH);
    delay(500);
    digitalWrite(this->shootPin, LOW);
    digitalWrite(this->focusPin, LOW);
}
void Camera::expoStart()
{

}
void Camera::expoStop()
{

}
