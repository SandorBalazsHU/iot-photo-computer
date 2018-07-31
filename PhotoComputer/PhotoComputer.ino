#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>
#include <Wire.h>
#include "OneWireButtons.h"

#define _DEBUG false
#define _UNIT_TEST false

const char* version = "Verzio: 1.0v"; 
const char photoIcon = (char)0;
const byte piezoPin = 8;
const byte focusPin = 9;
const byte shootPin = 10;
const byte keyBoardPin = 0;

LiquidCrystal_I2C lcd(0x27,20,4);
uint8_t photoIconPattern[8] = {0x0,0xe,0x1b,0x11,0x1b,0x1f,0x0,0x0};
virtuabotixRTC myRTC(13, 12, 11);
OneWireButtons keyBoard(keyBoardPin);


void setup() {
  #if _DEBUG || _UNIT_TEST
    Serial.begin(9600);
  #endif

  lcd.init();
  lcd.backlight();
  lcd.createChar(0, photoIconPattern);

  //myRTC.setDS1302Time(0, 30, 1, 5, 18, 7, 2018);

  pinMode(focusPin, OUTPUT);
  pinMode(shootPin, OUTPUT);

  printIntro();
}

void loop() {
  printTime();
  
  lcd.setCursor(15,0);
  lcd.print(photoIcon);

  int buttonValue = keyBoard.checkButtons();

  #if _DEBUG || _UNIT_TEST
    Serial.print(buttonValue);
    Serial.print(" , ");
    Serial.print(keyBoard.callibrationCheck());
  #endif

  lcd.setCursor(15,1);
  lcd.print(buttonValue);

  if(buttonValue > 0){
    tone(piezoPin, 3000, 100);
  }

  if(buttonValue == 3){
    digitalWrite(shootPin, HIGH);
    digitalWrite(focusPin, HIGH);
    delay(500);
    digitalWrite(shootPin, LOW);
    digitalWrite(focusPin, LOW);
  }

  if(buttonValue == 6){
    digitalWrite(focusPin, HIGH);
    delay(500);
    digitalWrite(focusPin, LOW);
  }

  if(buttonValue == 4){
    lcd.noBacklight();
  }

  if(buttonValue == 5){
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

void printIntro() {
  tone(piezoPin, 3000, 100);
  lcd.setCursor(0,0);
  lcd.print("SB PhotoComputer ");
  lcd.setCursor(0,1);
  lcd.print(version);
  delay(3000);
  lcd.clear();
}
