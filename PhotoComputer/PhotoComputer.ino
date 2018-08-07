#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>
#include <Wire.h>
#include "OneWireButtons.h"
#include "Camera.h"

const char* version = "1.1v StarTrailsTest"; 
const byte piezoPin = 8;
const byte focusPin = 9;
const byte shootPin = 10;
const byte keyBoardPin = 0;

LiquidCrystal_I2C lcd(0x27,20,4);
virtuabotixRTC myRTC(13, 12, 11);
OneWireButtons keyBoard(keyBoardPin);

void setup() {
  lcd.init();
  lcd.backlight();
  printIntro();
}

void loop() {
  printTime();

  int buttonValue = keyBoard.checkButtons();

  if(buttonValue > 0){
    tone(piezoPin, 3000, 100);
  }

  if(buttonValue == 3){
  }

  delay(200);
}

void printTime() {
  myRTC.updateTime();
  lcd.setCursor(0,0);
  lcd.print(myRTC.year);
  lcd.print("/");
  lcd.print(myRTC.month);
  lcd.print("/");
  lcd.print(myRTC.dayofmonth);
  
  lcd.setCursor(0,1);
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  lcd.print(":");
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