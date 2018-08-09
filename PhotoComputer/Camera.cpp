#include <Arduino.h>
#include "Camera.h"

Camera::Camera(byte expoPin, byte focusPin, byte piezoPin) : expoPin(expoPin), focusPin(focusPin), piezoPin(piezoPin)
{
    this->startTime = 0;
    this->currentTime = 0;
    this->startSemafor = 0;
    this->focusState = 0;
    this->expoState = 0;
}
void Camera::setup()
{
    pinMode(this->expoPin, OUTPUT);
    pinMode(this->focusPin, OUTPUT);
    delay(this->singleExpoTime);
    digitalWrite(this->expoPin, LOW);
    digitalWrite(this->focusPin, LOW);
    delay(this->singleExpoTime);
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
int Camera::exposition(byte time)
{
    if(this->startSemafor == 0)
    {
        this->startTime = millis();
        this->startSemafor = 1;
        digitalWrite(this->focusPin, HIGH);
        digitalWrite(this->expoPin, HIGH);
    }

    this->currentTime = millis();

    if(this->currentTime - this->startTime >= time )
    {
        digitalWrite(this->focusPin, LOW);
        digitalWrite(this->expoPin, LOW);
        return 1;
    }
    else
    {
        return 0;
    }
}
void Camera::singleExpo()
{
    digitalWrite(this->expoPin, HIGH);
    digitalWrite(this->focusPin, HIGH);
    delay(this->singleExpoTime);
    tone(this->piezoPin, 3000, 100);
    digitalWrite(this->expoPin, LOW);
    digitalWrite(this->focusPin, LOW);
}
void Camera::expoStart()
{
    digitalWrite(this->focusPin, HIGH);
    delay(this->singleExpoTime);
    digitalWrite(this->expoPin, HIGH);
    delay(this->singleExpoTime);
    this->focusState = 1;
    this->expoState = 1;
}
void Camera::expoStop()
{
    digitalWrite(this->expoPin, LOW);
    delay(this->singleExpoTime);
    digitalWrite(this->focusPin, LOW);
    delay(this->singleExpoTime);
    this->focusState = 0;
    this->expoState = 0;
}
