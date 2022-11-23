#include <Servo.h>
Servo servo;

int value = 0;

void setup() {
  servo.attach(7);
}

void loop() {
  value = 0;
  servo.write(vlaue);
  delay(500);

  value = 45;
  servo.write(value);
  delay(500);

  value = 90;
  servo.write(value);
  delay(500);

  value = 135;
  servo.write(value);
  delay(500);
  
  value = 170;
  servo.write(value);
  delay(500);
}