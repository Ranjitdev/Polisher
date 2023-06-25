// Speed increases by 46 RPM & 47 RPM each
// Actual percentage increases by 2% each
// Avarage percentage increase by 3% each
// On start up pot need to be more than actual percentage 41% or avarage percentage 15% or 188 RPM
// Minimum speed of 1 RPM with avarage percentage 1% reached on actual percentage 32%
// Near minimum speed alarm starts at actual percentage 41% or avarage percentage 15% or 188 RPM
// Minimum speed alarm 1 RPM with avarage percentage 1% reached on actual percentage 30%

#include <LiquidCrystal.h>
#define triac 3
#define pot A0
#define zerocross 2
const int ok_swich = A1;
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int pot_val = 0;
int pot_val_old;
int speed_curr = 0;
int speed_av;
int percent_av;
int percent_av1;

void setup() {
    pinMode(triac, OUTPUT);
    pinMode(zerocross, INPUT);
    pot_val_old = analogRead(pot);
    speed_curr = map(pot_val_old, 0, 900, 6, 50);
    Serial.begin(9600);
    lcd.begin(16, 2);
    
    lcd.setCursor(1, 0);
    lcd.print("APOLLO INSTRUMENTS & EQUIPMENT");
    for(int pos = 0; pos <= 14; pos++){
        lcd.scrollDisplayLeft();
        delay(700);
    }
    lcd.clear();

    while(speed_curr >= 32){
      pot_val_old = analogRead(pot);
      speed_curr = map(pot_val_old, 0, 900, 6, 50);
      percent_av1 = map(speed_curr, 6, 50, 100, 0);
      lcd.setCursor(0,1);
      lcd.print("Increase Percent");
      lcd.setCursor(0,0);
      lcd.print("Percentage ");
      lcd.print(percent_av1);
      lcd.print(" %");
      delay(50);
      lcd.clear();
    }
    lcd.clear();
    digitalWrite(triac, HIGH);
    delayMicroseconds(100);
    digitalWrite(triac, LOW);
    
    Serial.println("usb command panel don't use if not necessay or not a developer");
    Serial.println("DEVELOPER RANJIT KUNDU");
    
    attachInterrupt(digitalPinToInterrupt(2), zero_cross, FALLING); 
}

void zero_cross()
{
  if(speed_curr >= 36){
    speed_curr = 36;
  }
  int dim = (200*speed_curr);
  delayMicroseconds(dim);  
  digitalWrite(triac, HIGH);
  delayMicroseconds(10);
  digitalWrite(triac, LOW);
}

void loop() {
  pot_val = analogRead(pot);
  speed_curr = map(pot_val, 0, 900, 6, 50);
  percent_av1 = map(speed_curr, 6, 50, 100, 0);
  if(speed_curr>=32 && speed_curr<=36){
    lcd.setCursor(0,0);
    lcd.print("Speed ");
    lcd.print(speed_av);
    lcd.print(" RPM");
    lcd.setCursor(0,1);
    lcd.print("Near Minimum ");
    lcd.print(percent_av1);
    lcd.print("%");
    delay(700);
    lcd.clear();
  }
  else if(speed_curr>=36){
    lcd.setCursor(0,0);
    lcd.print("Lowest Speed ");
    lcd.print(speed_av);
    lcd.setCursor(0,1);
    lcd.print("Min Reached ");
    lcd.print(percent_av1);
    lcd.print("%");
    delay(700);
    lcd.clear();
    speed_curr = 36;
  }
  
  lcd.setCursor(0,1);
  percent_av = map(speed_curr, 6, 36, 100, 1);
  lcd.print("Percentage ");
  lcd.print(percent_av);
  lcd.print("%");
  speed_av = map(speed_curr, 6, 36, 1400, 1);
  lcd.setCursor(0,0);
  lcd.print("Speed ");
  lcd.print(speed_av);
  lcd.print(" RPM");
  delay(1000);
  lcd.clear();
}
