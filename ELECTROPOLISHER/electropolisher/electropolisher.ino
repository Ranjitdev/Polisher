

#include <LiquidCrystal.h>
const int ok_swich = A2;
const int inc_swich = A0;
const int dec_swich = A1;
const int led1 = 12;
const int led2 = 13;
unsigned long timer = 0;
unsigned long timer1 = 0;
unsigned long timer2 = 0;
int ok_timer = 0;
unsigned long st_time = 0;
unsigned long end_time = 0;
int exit1 = LOW;
int exit2 = LOW;

int speakerPin = 11;
int length = 15; 
char notes[] = "ccggaagffeeddc ";
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 }; 
int tempo = 300; 

void playTone(int tone, int duration) { 
    for (long i = 0; i < duration * 1000L; i += tone * 2) { 
        digitalWrite(speakerPin, HIGH); 
        delayMicroseconds(tone); 
        digitalWrite(speakerPin, LOW); 
        delayMicroseconds(tone); 
    } 
} 

void playNote(char note, int duration) { 
    char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' }; 
    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 }; 
    
    for (int i = 0; i < 8; i++) { 
        if (names[i] == note) { 
            playTone(tones[i], duration); 
        } 
    } 
}

const int rs = 6, en = 7, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
    
    pinMode(ok_swich, INPUT);
    pinMode(speakerPin, OUTPUT);
    pinMode(inc_swich, INPUT);
    pinMode(dec_swich, INPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    Serial.begin(9600);
    lcd.begin(16, 2);
    
    lcd.setCursor(1, 0);
    lcd.print("APOLLO INSTRUMENTS & EQUIPMENT");
    for(int pos = 0; pos <= 14; pos++){
        lcd.scrollDisplayLeft();
        delay(700);
    }
    lcd.clear();
    
    Serial.println("usb command panel don't use if not necessay or not a developer");
    Serial.println("DEVELOPER RANJIT KUNDU");
     
}

void loop() {
    timer1 = 60;
    timer2 = 30;
    timer = 0;
    Serial.println("main program started");
    
    exit1 = LOW;
    timer = 0;
    
    timer01();
    
    exit2 = LOW;
    timer = 0;
    
    timer02();
        
    delay(1000);
    
    int exit = LOW;
    while(exit != HIGH){
        Serial.println("Press OK To Start");
        exit = digitalRead(ok_swich);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pol ");
        lcd.setCursor(4, 0);
        lcd.print(timer1);
        lcd.setCursor(9, 0);
        lcd.print("Eac ");
        lcd.setCursor(13, 0);
        lcd.print(timer2);
        lcd.setCursor(0, 1);
        lcd.print("Press OK Or RES");
        delay(100);
    }
    
    lcd.clear();
    Serial.println("INPUT TAKEN");
    
    lcd.setCursor(0, 0);
    lcd.print("Polish Started");
    lcd.setCursor(0, 1);
    lcd.print("For ");
    lcd.print(timer1);
    lcd.print(" sec");
    digitalWrite(led1, HIGH);
    timer1 = timer1 * 1000;
    delay(timer1);
    Serial.println(timer1);
    Serial.println("timer 1 completed");
    digitalWrite(led1, LOW);
    tone( speakerPin, 440, 100);
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("Each Started");
    lcd.setCursor(0, 1);
    lcd.print("For ");
    lcd.print(timer2);
    lcd.print(" sec");
    digitalWrite(led2, HIGH);
    timer2 = timer2 * 1000;
    delay(timer2);
    Serial.println(timer2);
    Serial.println("timer 2 completed");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Treatment End...");
    digitalWrite(led2, LOW);
    for (int i = 0; i < length; i++) { 
        if (notes[i] == ' ') { 
            delay(beats[i] * tempo);
            } 
        else { 
            playNote(notes[i], beats[i] * tempo); 
            } 
        delay(tempo / 2);
    }
    lcd.clear();
    Serial.print("program completed");
}

void timer01(){
    int i = 0;
    if (exit1 != HIGH){
        for(i=900; i>=0; i-- ){
            exit1 = digitalRead(ok_swich);
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("Counting ");
            lcd.print(i/10);
            lcd.print(" sec");
            lcd.setCursor(0, 0);
            lcd.print("Polishing ");
            lcd.print(timer1);
            Serial.print("Polishing = ");
            Serial.println(timer1);
            delay(100);
            inc_dec();
            timer1 = timer;
            if(timer1 >= 180){
                timer1 = 180;
            }
            if(digitalRead(ok_swich) == HIGH){
                i = 0;
                delay(500);
            }
       } 
    }
}

void timer02(){
    int i = 0;
    if (exit2 != HIGH){
        for(i=600; i>=0; i-- ){
            exit2 = digitalRead(ok_swich);
            lcd.clear();
            lcd.setCursor(0, 1); 
            lcd.print("Counting ");
            lcd.print(i/10);
            lcd.print(" sec");
            lcd.setCursor(0, 0);
            lcd.print("Eaching = ");
            lcd.print(timer2);
            Serial.print("Eaching = ");
            Serial.println(timer2);
            delay(100);
            inc_dec();
            timer2 = timer;
            if(timer2 >= 120){
                timer2 = 120;
            }
            if(digitalRead(ok_swich) == HIGH){
                i = 0;
                delay(500);
            }
        }
    }
}

void inc_dec(){
    int increament = digitalRead(inc_swich);
    int decreament = digitalRead(dec_swich);
    if (increament == HIGH){
        increament = LOW;
        timer = timer+1;
        Serial.print("increased = ");
        Serial.println(timer);
        delay(100);
            
    }
    if (decreament == HIGH){
        decreament = LOW;
        timer = timer-1;
        Serial.print("Decreased = ");
        Serial.println(timer);
        delay(100);
    }
}
