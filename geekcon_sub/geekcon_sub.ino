
#include <Servo.h> 

//static int LED = 2;
static int REMOTE_R = 2;  
static int REMOTE_L = 3;
static int REMOTE_F = 4;
static int SERVO_PIN = 5;
static int MOTOR_PIN = 6;

static const int DEG_DELTA = 20;

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
  if (forward) {
    digitalWrite(MOTOR_PIN, HIGH);
  }

  direction_servo.write(90);
  if (right) {
    direction_servo.write(90 - DEG_DELTA);
  }
  if (left) {
    direction_servo.write(90 + DEG_DELTA);
  }
  
  delay(1);
}   
