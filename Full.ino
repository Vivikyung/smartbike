#include <rgb_lcd.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include "MMA7660.h"

MMA7660 accelemeter;

rgb_lcd lcdFront;
LiquidCrystal lcdLeft(8, 7, 10, 11, 12, 13);
LiquidCrystal lcdRight(8, 9, 10, 11, 12, 13);

//blinker system variables
int l_LCD = A0;
int r_LCD = A1;
int left_on = 0;
int right_on = 0;
int leftBut = 2;
int rightBut = 3;
int leftLED = 4;
int rightLED = 5;

//measures light
int photoCell = A4;
int photoReading;
int dim = 0;
int count = 0;

//accelerometer information
float v0 = 0;
float vf = 0;
float ax, ay, az;
float accel;
float tTot = 0;
float tNow = 0;

void setup() {
  Serial.begin(9600);
  pinMode(l_LCD, OUTPUT);
  pinMode(r_LCD, OUTPUT);
  
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);

  pinMode(photoCell, INPUT);

  lcdFront.begin(16,2);
  lcdLeft.begin(16,2);
  lcdRight.begin(16,2);
  accelemeter.init();

  //set up initial light
//  photoReading = analogRead(photoCell);
//  if(photoReading < 500){
//    dim = 100;
//    analogWrite(l_LCD, dim);
//    analogWrite(r_LCD, dim);
//  }
//  Serial.print("Dim is: ");
//  Serial.println(dim);

  pinMode(leftBut, INPUT);
  pinMode(rightBut, INPUT);
  attachInterrupt(digitalPinToInterrupt(leftBut), L_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(rightBut), R_ISR, RISING);
}

void loop() {
  accelemeter.getAcceleration(&ax, &ay, &az);
  accel = calculate_a(ay);
  //Serial.print("accel: ");
  //Serial.println(accel);
  tNow = (millis() - tTot)/1000;
  //Serial.print("tnow: ");
  //Serial.println(tNow);
  tTot += tNow;
  vf = v0 + accel*tNow;
  v0 = vf;
  //lcdFront.print(vf);

//  if(ax < 0 || ay < 0 ){
//    analogWrite(l_LCD, 200);
//    analogWrite(r_LCD, 200);
//  }
  
  while(left_on == 1){
    analogWrite(l_LCD, 250);
    digitalWrite(leftLED, HIGH);
    delay(800);
    analogWrite(l_LCD, dim);
    digitalWrite(leftLED, LOW);
    delay(800);
  }
  while(right_on == 1){
    analogWrite(r_LCD, 250);
    digitalWrite(rightLED, HIGH);
    delay(800);
    analogWrite(r_LCD, dim);
    digitalWrite(rightLED, LOW);
    delay(800);
  }

  count++;
  if(count == 1000){
    Serial.println("Checking brightness now");
    lcdFront.clear();
    delay(500);
    photoReading = analogRead(photoCell);
    lcdFront.print(photoReading);
    Serial.println(photoReading);
    if(photoReading < 750){
      analogWrite(l_LCD, 150);
      analogWrite(r_LCD, 150);
    }else{
      analogWrite(l_LCD, 0);
      analogWrite(r_LCD, 0);
    }
    count = 0;
  }

}

float calculate_a(float x){
  return x * 9.8;
}

void L_ISR(){
  if(left_on == 0){
    left_on = 1;
    Serial.println("Left on!");
  }else{
    left_on = 0;
    Serial.println("Left off!");
  }
}

void R_ISR(){
  if(right_on == 0){
    right_on = 1;
    Serial.println("Right on!");
  }else{
    right_on = 0;
    Serial.println("Right off!");
  }
}

