#include <rgb_lcd.h>
#include <Wire.h>

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

void setup() 
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    //lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    lcd.print("hello, world!");

    delay(1000);
}

void loop() 
{
    lcd.clear();
    lcd.setRGB(0,0,0);
    lcd.setCursor(0,0);
    delay(1000);
    lcd.setRGB(255,0,0);
    delay(1000);
    lcd.setRGB(0,255,0);
    delay(1000);
    lcd.setRGB(0,0,255);
    delay(1000);

    delay(100);
}
