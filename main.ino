#include <SoftwareSerial.h>
#include <Stepper.h>
#include <Servo.h>

Servo Z;
Servo claw;

#define DELAY 5
#define DOWN A0
#define UP A1
#define RIGHT A2
#define LEFT A3

#define BUTTON A4


const int stepsPerRevolution = 200;
Stepper X = Stepper(stepsPerRevolution, 2, 3, 4, 5);
Stepper Y = Stepper(stepsPerRevolution, 6, 7, 8, 9
);


void setStepperIdle() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);

}

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(UP, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(BUTTON, INPUT_PULLUP);

  claw.attach(10);
  Z.attach(11);
  setStepperIdle();
}



void loop() {
  int up = 0;
  int right = 0;
  int left = 0;
  int down = 0;
  int button = 0;

  up = digitalRead(UP);
  right = digitalRead(RIGHT);
  left = digitalRead(LEFT);
  down = digitalRead(DOWN);
  button = digitalRead(BUTTON);
  
  if (up == LOW) {
    X.step(5);
    Serial.write("u");
  }
  if (right == LOW) Y.step(5);
  if (left == LOW) Y.step(-5);
  if (down == LOW) X.step(-5);
  if(button == LOW) {
    Serial.write("L");
    Z.write(20);
    delay(1800);
    Z.write(90);
    delay(1000);
    Z.write(160);
    delay(1800);
    Z.write(90);
    
  }
  delay(1);

  if (up != LOW && right != LOW && left != LOW && down != LOW) setStepperIdle(); // 모터 드라이버 과열 방지
}
