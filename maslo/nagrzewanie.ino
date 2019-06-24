#include <LiquidCrystal.h>
#define a -4.87782690794794e-07
#define b 0.000812680682893712
#define c -0.557577238089082
#define d 242.679245990164
#define Heater_0      10

LiquidCrystal lcd(16,17,23,25,27,29);
int temp, i = 0,e,u;
double x,y;

void setup() {
  lcd.begin( 20,4 );
  pinMode(Heater_0, OUTPUT);

}

void loop() {

  // nagrzewanie
//  if( i < 50 )
//  {
//    digitalWrite(Heater_0,HIGH);
//    i++;
//  }
//  else
//  {
//    digitalWrite(Heater_0,LOW);
//  }

  //zabawa w wyswietlanie
  lcd.setCursor(0,0);
  lcd.print("Hello There.");
  lcd.setCursor(0,1);
  lcd.print("General Kenobi...");

  //wlasciwa czesc
  temp = analogRead(13);
  x = (double)temp;
  y =a*x*x*x + b*x*x + c*x + d;
  lcd.setCursor(0,2);
  lcd.print("Temprature :");
  lcd.setCursor(13,2);
  lcd.print(y);

  //regulowanko
  e = 100 - y;
  u = round(255*e/80); // 80 to maksymalny blad
  if(u>255) u = 255;
  if(u<0) u = 0;
  analogWrite(10, u);

  delay(100);
  lcd.setCursor(0,3);
  lcd.print(i);
  
}
