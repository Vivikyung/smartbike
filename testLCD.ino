#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
//LiquidCrystal lcd2(7, 13, 9, 10, 11, 12);

int switcheroo = A0;

void setup() { 
  lcd.begin(16, 2);
  //lcd2.begin(16, 2);
  analogWrite(switcheroo, 250);
}

void loop() { 
  //lcd2.setCursor(0,1);
  //lcd2.write("yo");
  delay(1000);
  analogWrite(switcheroo, 0);
  delay(1000);
  analogWrite(switcheroo, 250);
  delay(1000);
  //lcd1.clear();
  //lcd1.noDisplay();
  //lcd2.clear();
  //lcd2.noDisplay();
  //delay(1000);
}
