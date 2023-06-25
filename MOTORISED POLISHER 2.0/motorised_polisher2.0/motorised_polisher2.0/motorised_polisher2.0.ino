#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <LiquidCrystal.h>
const int rs = 10, en = 9, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define relay 13
#define swich 11
#define led 3
#define sensor 2

unsigned long rpmtime;
float rpmfloat;
unsigned int rpm;
bool slow = 1;

void setup() {
  lcd.begin(16, 2);
  pinMode(relay, OUTPUT);
  pinMode(swich, INPUT);
  pinMode(led, OUTPUT);
  pinMode(sensor, INPUT);

  digitalWrite(led, LOW);
  digitalWrite(relay, LOW);

  logo();

  swich_on();
  
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << CS12); //Prescaler 256
  TIMSK1 |= (1 << TOIE1); //enable timer overflow
  attachInterrupt(0, RPM, RISING);
}

ISR(TIMER1_OVF_vect) {
  slow = 1;
}

void loop() {

  delay(500);
  if (slow == 1) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("SLOW SPEED...");
  lcd.setCursor(0,1);
  lcd.print("INCREASE SPEED");
  }
  else {
    rpmfloat = 120 / (rpmtime/ 31250.00);
    rpm = round(rpmfloat);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("MOTOR SPEED...");
    lcd.setCursor(0,1);
    lcd.print( rpm);
    lcd.print(" RPM");
  }
}

void RPM () {
  rpmtime = TCNT1;
  TCNT1 = 0;
  slow = 0;
}

void logo(){
  
  lcd.setCursor(1, 0);
    lcd.print("APOLLO INSTRUMENTS & EQUIPMENT");
    for(int pos = 0; pos <= 14; pos++){
        lcd.scrollDisplayLeft();
        delay(600);
    }
    lcd.clear();
}

void swich_on(){
  unsigned int m = 0;
  digitalWrite(led, HIGH);
  
  while(digitalRead(swich) != HIGH){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("MOTOR OFF");
    lcd.setCursor(0,1);
    lcd.print("PRESS ON  ");
    lcd.print(m/1000);
    m = millis();
    delay(300);
  }

  digitalWrite(relay, HIGH);
  digitalWrite(led, LOW);
}
