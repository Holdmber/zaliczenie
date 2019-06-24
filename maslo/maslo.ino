
#define X_MIN_PIN           3
#ifndef X_MAX_PIN
  #define X_MAX_PIN         2
#endif
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#ifndef X_CS_PIN
  #define X_CS_PIN         53
#endif

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#ifndef Y_CS_PIN
  #define Y_CS_PIN         49
#endif

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#ifndef Z_CS_PIN
  #define Z_CS_PIN         40
#endif

#define E0_STEP_PIN        26
#define E0_DIR_PIN         28
#define E0_ENABLE_PIN      24
#ifndef E0_CS_PIN
  #define E0_CS_PIN        42
#endif

#define E1_STEP_PIN        36
#define E1_DIR_PIN         34
#define E1_ENABLE_PIN      30
#ifndef E1_CS_PIN
  #define E1_CS_PIN        44
 #endif

#include <LiquidCrystal.h>
#define a -4.87782690794794e-07
#define b 0.000812680682893712
#define c -0.557577238089082
#define d 242.679245990164
#define Heater_0      10

int i=0;
bool kier1 = 0, kier2 = 0, kier3 = 0;
String bufor;
int k1 = 0, k2 = 0, k3 = 0;
bool czy_mam_odp = 0;

void setup() {
  Serial.begin(115200);
  pinMode(X_ENABLE_PIN, OUTPUT);
  digitalWrite(X_ENABLE_PIN,LOW);
  
  pinMode(Y_ENABLE_PIN, OUTPUT);
  digitalWrite(Y_ENABLE_PIN,LOW);
  
  pinMode(Z_ENABLE_PIN, OUTPUT);
  digitalWrite(Z_ENABLE_PIN,LOW);
   
   pinMode(X_DIR_PIN , OUTPUT);
  digitalWrite(X_DIR_PIN ,LOW);
  
  pinMode(Y_DIR_PIN , OUTPUT);
  digitalWrite(Y_DIR_PIN ,LOW);
  
  pinMode(Z_DIR_PIN , OUTPUT);
  digitalWrite(Z_DIR_PIN ,LOW);

  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Z_STEP_PIN, OUTPUT);

  pinMode(X_MAX_PIN, INPUT_PULLUP);
  pinMode(Y_MAX_PIN, INPUT_PULLUP);
  pinMode(Z_MAX_PIN, INPUT_PULLUP);
  
  lcd.begin( 20,4 );
  pinMode(Heater_0, OUTPUT); 
}

void loop() {

// --------------- krok ------------------  
  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  delay(2);
  if(digitalRead(X_MAX_PIN)==0 && k1 > 0)
    {
        digitalWrite(X_STEP_PIN, HIGH);
        k1--;
    }
  if(digitalRead(Y_MAX_PIN)==0 && k2 > 0)
    {
        digitalWrite(Y_STEP_PIN, HIGH);
        k2--;
    }
  if(digitalRead(Z_MAX_PIN)==0 && k3 > 0)
    {
        digitalWrite(Z_STEP_PIN, HIGH);
        k3--;
    }
    delay(2);

// --------------- czytanie polecenia ------------------  
  while(Serial.available() > 0)
  {
    bufor = Serial.readStringUntil('\n');
    sscanf(bufor.c_str(),"k1 %d; k2 %d; k3 %d",&k1,&k2,&k3);
    czy_mam_odp = 1; // ustawiane na 1, aby uniknac powielania komunikatu "maslo"
//    Serial.println(k1);
//    Serial.println(k2);
//    Serial.println(k3);

    kier1 = k1 < 0;
    k1 = k1 > 0 ? k1 : -k1;
    digitalWrite(X_DIR_PIN, kier1);

    kier2 = k2 < 0;
    k2 = k2 > 0 ? k2 : -k2;
    digitalWrite(Y_DIR_PIN, kier2);
  
    kier3 = k3 < 0;
    k3 = k3 > 0 ? k3 : -k3;
    digitalWrite(Z_DIR_PIN, kier3);
  }
// --------------sprawdzanie ukonczenia ruchu----------------
   if(k1 == 0 && k2 == 0 && k3 == 0 && czy_mam_odp == 1)
   {
      Serial.println("maslo"); 
      czy_mam_odp = 0;
   }
  
  
// ----------------------------------------------------------
  // ----------------- CZESC NAGRZEWAJACA -------------------
// ----------------------------------------------------------
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

