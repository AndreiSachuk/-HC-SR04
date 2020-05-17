#include <LiquidCrystal.h>
#include <TimerMillis.h>
#include <Wire.h>
TimerMillis timer;
LiquidCrystal lcd(9 , 8, 7, 6, 5, 4);
const int trigPin = 2;
const int echoPin = 3;
const int button = 10;
long duration;
int distanceCm, distanceInch;
int flag;

void setup() {
lcd.begin(16,2); 
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(button, INPUT_PULLUP);
lcd.setCursor(0,0);
lcd.print("IZMER  ULTRAZVUK");
}

void loop() {
if (digitalRead(button)==0){
flag = 1;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distanceCm= duration*0.034/2;

if (distanceCm>400 || distanceCm<2) {
lcd.setCursor(0,1);
lcd.print("                "); 
lcd.setCursor(2,1); 
lcd.print("OUT OF RANGE");
timer.zero();
} else {
lcd.setCursor(0,1);
lcd.print("                "); 
lcd.setCursor(0,1);
lcd.print("Distance:");
lcd.print(distanceCm);
lcd.setCursor(14,1);
lcd.print("cm");
timer.zero();}}
if (timer.get()>2000 && flag==1) {
  lcd.setCursor(0,1);
  lcd.print("                ");
  flag = 0;}
  else {if (timer.get()>2000){
  lcd.setCursor(2,1);
  lcd.print("PRESS BUTTON"); 
}

}
}
