
#include <Servo.h> 

const static int SERVO_PIN = 6;

Servo direction_servo; 

void setup() {
  // put your setup code here, to run once:
  direction_servo.attach(SERVO_PIN);

}

static int servo_dir = 0;

void loop() {
  // put your main code here, to run repeatedly:
  direction_servo.write(servo_dir);
  servo_dir += 1;
  servo_dir = servo_dir % 360;
  delay(10);

}
