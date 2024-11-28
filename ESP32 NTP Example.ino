#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"
const int potentiometerPin = 33; 
const int ledPin = 4; 
#define DHTPIN 13      
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE); 
int lcdColums = 20;
int lcdrows = 4;
LiquidCrystal_I2C lcd(0x27,lcdColums,lcdrows);

void setup(){
  Serial.begin(9600);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
  pinMode(ledPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Test");
  lcd.clear();
}
void loop(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.setCursor(3,0);
  lcd.print("Humi=" + String(h)+"%");
  lcd.setCursor(3,1);
  lcd.print("Temp=" + String(t)+"C");
  
  int potValue = analogRead(potentiometerPin);
  int ledIntensity = map(potValue, 0, 4095, 0, 255);
  analogWrite(ledPin, ledIntensity);
  Serial.print("Potentiometer: ");
  Serial.print(potValue);
  Serial.print(" | LED Intensity: ");
  Serial.println(ledIntensity);
  
  if (potValue < 1024) {
    digitalWrite(4, HIGH); 
  } else if (potValue < 2048) {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  } else {
    digitalWrite(4, LOW); 
  }
  delay(100); 
}