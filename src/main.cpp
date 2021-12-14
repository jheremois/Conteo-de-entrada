#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// variables del pantalla
int lcdColumns = 16;
int lcdRows = 2;

// variables del Utra sonido
int TRIG = 15;
int EHCO = 4;
int BIB = 14;
int ELLED = 13;
int DURACION;
int DISTANCIA;
int count = 1;

// Personas que han entrado


LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 

void setupLcd(){
  lcd.init();
}

void setupUltaSonic(){
  pinMode(TRIG, OUTPUT);
  pinMode(EHCO, INPUT);
  pinMode(BIB, OUTPUT);
  pinMode(ELLED, OUTPUT);
  Serial.begin(9600);
}

void displayCount(){
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.printf("Bienvenido!");
  lcd.setCursor(0, 1);
  lcd.printf("Entrada no: %d", count++);
  delay(6000);
  lcd.clear();
  delay(1000);
  lcd.noBacklight();
  delay(500);
}

void detectsPerson(){

  digitalWrite(TRIG, HIGH);
  delay(1);
  digitalWrite(TRIG, LOW);
  
  DURACION = pulseIn(EHCO, HIGH);
  DISTANCIA = DURACION / 58.2;
  Serial.println(DISTANCIA);
  delay(200);

  if (DISTANCIA <= 70 && DISTANCIA >= 1){
    digitalWrite(ELLED, HIGH);
    digitalWrite(BIB, HIGH);
    delay(700);
    digitalWrite(BIB, LOW);
    displayCount();
  }else{
    digitalWrite(ELLED, LOW);
    
  }
}

void setup(){
  setupLcd();
  setupUltaSonic();
}
void loop(){
  detectsPerson();
}