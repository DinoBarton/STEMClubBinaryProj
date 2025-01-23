#include <LiquidCrystal.h>

const int rs = 12, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int button1 = 11;
const int LED1 = 9;

const int button0 = 10;
const int LED0 = 8;

bool led1State = false;
bool button1State = false;
bool lastButton1State = false;

bool led0State = false;
bool button0State = false;
bool lastButton0State = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(button1, INPUT);
  pinMode(LED1, OUTPUT);

  pinMode(button0, INPUT);
  pinMode(LED0, OUTPUT);

  lcd.print("123");
}

void loop() {
  // put your main code here, to run repeatedly:
  button1State = digitalRead(button1);

  if (button1State == HIGH && lastButton1State == LOW) {
    led1State = !led1State;
    digitalWrite(LED1, led1State ? HIGH : LOW);
    
    }

  lastButton1State = button1State;

  button0State = digitalRead(button0);

  if (button0State == HIGH && lastButton0State == LOW) {
    led0State = !led0State;
    digitalWrite(LED0, led0State ? HIGH : LOW);
    
    }
   
  lastButton0State = button0State; 
} 
