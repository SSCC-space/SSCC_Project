#include <SoftwareSerial.h>
#include <AFMotor.h>
#define TRIG_F A0 //TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO_F A1 //ECHO 핀 설정 (초음파 받는 핀)
#define TRIG_L A2 //TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO_L A3 //ECHO 핀 설정 (초음파 받는 핀)
#define TRIG_R A4 //TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO_R A5 //ECHO 핀 설정 (초음파 받는 핀)


AF_DCMotor motor_1(1);
AF_DCMotor motor_2(2);

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_F, OUTPUT);
  pinMode(ECHO_F, INPUT);
  pinMode(TRIG_L, OUTPUT);
  pinMode(ECHO_L, INPUT);
  pinMode(TRIG_R, OUTPUT);
  pinMode(ECHO_R, INPUT);
  motor_1.setSpeed(50);
  motor_2.setSpeed(50);
  motor_1.run(RELEASE);
  motor_2.run(RELEASE);
}

void loop() {
  int F_distance = Get_distance(TRIG_F, ECHO_F);
  int L_distance = Get_distance(TRIG_L, ECHO_L);
  int R_distance = Get_distance(TRIG_R, ECHO_R);
  if (F_distance <= 20) {
    Stop();
  }
  else {
    Go();
  }
}

int Get_distance(int TRIG, int ECHO) {
  long duration, distance;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn (ECHO, HIGH);
  distance = duration * 17 / 1000; 
  return distance;
}

void Go() {
  motor_1.setSpeed(70);
  motor_2.setSpeed(70);
  motor_1.run(FORWARD);
  motor_2.run(FORWARD);

}

void Left() {
  motor_1.run(FORWARD);
  motor_2.run(BACKWARD);
}

void Right() {
  motor_1.run(BACKWARD);
  motor_2.run(FORWARD);
}

void Back() {
  motor_1.run(BACKWARD);
  motor_2.run(BACKWARD);
}

void Stop() {
  motor_1.run(RELEASE);
  motor_2.run(RELEASE);
}