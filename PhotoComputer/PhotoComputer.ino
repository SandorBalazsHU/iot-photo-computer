#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>
#include <Wire.h>
#include "OneWireButtons.h"
#include "Camera.h"
#include "Time.h"

const char* version = "StarTrailsTest"; 
const byte piezoPin = 8;
const byte focusPin = 9;
const byte expoPin = 10;
const byte keyBoardPin = 0;

Time startTime;
Time currentTime;
int expoTime = 30;
int expoCounter = 0;
int state = 0;

LiquidCrystal_I2C lcd(0x27,20,4);
virtuabotixRTC myRTC(13, 12, 11);
OneWireButtons keyBoard(keyBoardPin);
Camera camera(expoPin, focusPin, piezoPin);

void setup()
{
  lcd.init();
  lcd.backlight();
  camera.setup();
  printIntro();
  startTime.set(myRTC);
  currentTime.set(myRTC);
}

void loop()
{
  printTime();
  
  if(timeToInt() >= currentTime.toInt() && state != 0)
  {
    camera.singleExpo();
    ++expoCounter;
    currentTime.add_sec(expoTime);
    camera.singleExpo();
  }

  int buttonValue = keyBoard.checkButtons();
  
  if(buttonValue > 0){
    tone(piezoPin, 3000, 100);
    lcd.clear();
  }
  if(buttonValue == 4) expoTime+=5;
  if(buttonValue == 5) expoTime-=5;
  if(buttonValue == 6)
  {
    if(state == 0)
    {
      camera.singleExpo();
      ++expoCounter;
      currentTime.add_sec(expoTime);
      state = 1;
    }
    else
    {
      state == 1;
      camera.singleExpo();
    }
  }

  delay(200);
}

double timeToInt()
{
  myRTC.updateTime();
  double time = myRTC.seconds + (myRTC.minutes * 100.0) + (myRTC.hours * 10000.0);
  return time;
}

void printTime()
{
  lcd.setCursor(0,0);
  if(currentTime.h < 10) lcd.print(0);
  lcd.print(currentTime.h);
  if(currentTime.m < 10) lcd.print(0);
  lcd.print(currentTime.m);
  if(currentTime.s < 10) lcd.print(0);
  lcd.print(currentTime.s);
  
  lcd.setCursor(6,0);
  lcd.print(" n:");
  lcd.print(expoCounter);

  lcd.setCursor(11,0);
  lcd.print(" m:");
  lcd.print(expoTime/60);
  
  lcd.setCursor(6,1);
  lcd.print(" t:");
  lcd.print(expoTime);
  
  myRTC.updateTime();
  
  lcd.setCursor(0,1);
  if(myRTC.hours < 10) lcd.print(0);
  lcd.print(myRTC.hours);
  if(myRTC.minutes < 10) lcd.print(0);
  lcd.print(myRTC.minutes);
  if(myRTC.seconds < 10) lcd.print(0);
  lcd.print(myRTC.seconds);
}

void printIntro() {
  tone(piezoPin, 3000, 100);
  lcd.setCursor(0,0);
  lcd.print("SB PhotoComputer ");
  lcd.setCursor(0,1);
  lcd.print(version);
  delay(3000);
  lcd.clear();
}
