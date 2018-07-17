#include <LiquidCrystal_I2C.h>
#include  <virtuabotixRTC.h>
#include <Wire.h>
#include "OneWireButtons.h"

LiquidCrystal_I2C lcd(0x27,20,4);
uint8_t photoIconPattern[8] = {0x0,0xe,0x1b,0x11,0x1b,0x1f,0x0,0x0};
virtuabotixRTC myRTC(13, 12, 11);
char photoIcon;
int piezoPin = 8;

void setup() {
  //Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, photoIconPattern);
  //myRTC.setDS1302Time(0, 30, 1, 5, 18, 7, 2018);
  photoIcon = (char)0;
}

void loop() {
  printTime();
  
  lcd.setCursor(15,0);
  lcd.print(photoIcon);

  lcd.setCursor(13,1);
  int buttonValue = analogRead(A0);
  //Serial.println(buttonValue);
  lcd.print(buttonValue);
  if(buttonValue>200){
    tone(piezoPin, 3000, 100);
  }
  if(buttonValue<200){
    lcd.print("000");
  }
  if(buttonValue==977){
    lcd.noBacklight();
  }
  if(buttonValue==837){
    lcd.backlight();
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
