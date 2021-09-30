
#include <Servo.h> 

//static int LED = 2;
static int REMOTE_R = 2;
static int REMOTE_L = 3;
static int REMOTE_F = 4;
static int SERVO_PIN = 5;
static int MOTOR_PIN = 6;

Servo direction_servo; 

void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR_PIN, OUTPUT);
  direction_servo.attach(SERVO_PIN);
  
  pinMode(REMOTE_R, INPUT);
  pinMode(REMOTE_L, INPUT);
  pinMode(REMOTE_F, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  int right = digitalRead(REMOTE_R);
  int left = digitalRead(REMOTE_L);
  int forward = digitalRead(REMOTE_F);
  Serial.print(right);
  Serial.print(left);
  Serial.println(forward);

  digitalWrite(MOTOR_PIN, LOW);
  if (1) {
    digitalWrite(MOTOR_PIN, HIGH);
  }

  direction_servo.write(90);
  if (right) {
    direction_servo.write(0);
  }
  if (left) {
    direction_servo.write(180);
  }
  
  //analogWrite(SERVO_PIN, 255);
//  if (value > 500) {
//    Servo1.write(90);
//    digitalWrite(LED, HIGH);
//  } else {
//    Servo1.write(0);
//    digitalWrite(LED, LOW);
//  }
  delay(1);

  
}   
