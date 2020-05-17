#include <LiquidCrystal.h>
#include <TimerMillis.h>
#include <Wire.h>
TimerMillis timer;
LiquidCrystal lcd(9 , 8, 7, 6, 5, 4); //Выводы подключения дисплея

//настройка выводов HC-SR04
const int trigPin = 2;
const int echoPin = 3;

//Кнопка измерения
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
//Выводим на первую строку название
lcd.print("IZMER  ULTRAZVUK");
}
void loop() {
  //Если нажата кнопка, проводим измерение
  if (digitalRead(button)==0){
  flag = 1;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm= duration*0.034/2;
  //Если вышли за пределы измерения
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
      timer.zero();} //Обнуляем таймер
  }

  if (timer.get()>2000 && flag==1) {//Если время прошло больше чем 2 секунды
    lcd.setCursor(0,1);
    lcd.print("                ");
    flag = 0;}
    else {if (timer.get()>2000){
        lcd.setCursor(2,1);
        lcd.print("PRESS BUTTON"); //Выводим собщение надмите кнопку
        }
    }
}
