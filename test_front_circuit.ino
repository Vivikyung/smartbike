int LEDleft = 4;
int LEDright = 5;
int butLeft = 2;
int butRight = 3;
int photo = A0;
int photoReading;

int left_on = 0;
int right_on = 0;

void setup() {
  pinMode(LEDleft, OUTPUT);
  pinMode(LEDright, OUTPUT);
  pinMode(butLeft, INPUT);
  pinMode(butRight, INPUT);
  attachInterrupt(digitalPinToInterrupt(butLeft), L_ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(butRight), R_ISR, RISING);
  pinMode(photo, INPUT);

  Serial.begin(9600);
  Serial.println("hello");
}

void loop() {
  while(left_on == 1){
    digitalWrite(LEDleft, HIGH);
    delay(200);
    digitalWrite(LEDleft, LOW);
    delay(200);
  }
  while(right_on == 1){
    digitalWrite(LEDright, HIGH);
    delay(200);
    digitalWrite(LEDright, LOW);
    delay(200);
  }
}

void L_ISR(){
  Serial.println("Left on!");
  if(left_on == 0){
    left_on = 1;
  }else{
    left_on = 0;
  }
}

void R_ISR(){
  Serial.println("Right on!");
  Serial.println(right_on);
  if(right_on == 0){
    right_on = 1;
  }else{
    right_on = 0;
  }
  Serial.println(right_on);
}

