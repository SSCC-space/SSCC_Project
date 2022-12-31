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
AF_DCMotor motor_3(3);
AF_DCMotor motor_4(4);

void setup() {
  delay(5000);
  Serial.begin(9600);
  pinMode(TRIG_F, OUTPUT);
  pinMode(ECHO_F, INPUT);
  pinMode(TRIG_L, OUTPUT);
  pinMode(ECHO_L, INPUT);
  pinMode(TRIG_R, OUTPUT);
  pinMode(ECHO_R, INPUT);
  motor_1.setSpeed(100);
  motor_1.run(RELEASE);
  motor_2.setSpeed(100);
  motor_2.run(RELEASE);
}

void loop() {
  long F_duration, F_distance;
  long L_duration, L_distance;
  long R_duration, R_distance;
  digitalWrite(TRIG_F, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_F, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_F, LOW);
  F_duration = pulseIn (ECHO_F, HIGH); //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.
  //34000*초음파가 물체로 부터 반사되어 돌아오는시간 /1000000 / 2(왕복값이아니라 편도값이기때문에 나누기2를 해줍니다.)
 //초음파센서의 거리값이 위 계산값과 동일하게 Cm로 환산되는 계산공식 입니다. 수식이 간단해지도록 적용했습니다.
  F_distance = F_duration * 17 / 1000; 

  //PC모니터로 초음파 거리값을 확인 하는 코드 입니다.
  Serial.print("\nF_DIstance : ");
  Serial.print(F_distance); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
  Serial.println(" Cm");

  digitalWrite(TRIG_L, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_L, LOW);
  L_duration = pulseIn (ECHO_L, HIGH); //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.
  //34000*초음파가 물체로 부터 반사되어 돌아오는시간 /1000000 / 2(왕복값이아니라 편도값이기때문에 나누기2를 해줍니다.)
 //초음파센서의 거리값이 위 계산값과 동일하게 Cm로 환산되는 계산공식 입니다. 수식이 간단해지도록 적용했습니다.
  L_distance = L_duration * 17 / 1000; 

  //PC모니터로 초음파 거리값을 확인 하는 코드 입니다.
  Serial.print("L_DIstance : ");
  Serial.print(L_distance); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
  Serial.println(" Cm");

  digitalWrite(TRIG_R, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_R, LOW);
  R_duration = pulseIn (ECHO_R, HIGH); //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.
  //34000*초음파가 물체로 부터 반사되어 돌아오는시간 /1000000 / 2(왕복값이아니라 편도값이기때문에 나누기2를 해줍니다.)
 //초음파센서의 거리값이 위 계산값과 동일하게 Cm로 환산되는 계산공식 입니다. 수식이 간단해지도록 적용했습니다.
  R_distance = R_duration * 17 / 1000; 
  Serial.print("R_DIstance : ");
  Serial.print(R_distance); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
  Serial.println(" Cm");

  if (L_distance >= 10) {
    motor_1.setSpeed(70);
    motor_2.setSpeed(100);
    motor_1.run(FORWARD);
    motor_2.run(FORWARD);
  } else if (L_distance <= 7) {
    motor_1.setSpeed(100);
    motor_2.setSpeed(70);
    motor_1.run(FORWARD);
    motor_2.run(FORWARD);
  }

  if (F_distance <= 10) {
    motor_1.run(RELEASE);
    motor_2.run(RELEASE);
    delay(10000);
  }

  delay(100); //1초마다 측정값을 보여줍니다.
}






// #include <SoftwareSerial.h>

// #include <AFMotor.h>

// AF_DCMotor motor_1(1);
// AF_DCMotor motor_2(2);
// AF_DCMotor motor_3(3);
// AF_DCMotor motor_4(4);

// void setup() {
//   motor_1.setSpeed(100);
//   motor_1.run(RELEASE);
//   motor_2.setSpeed(100);
//   motor_2.run(RELEASE);
//   motor_3.setSpeed(100);
//   motor_3.run(RELEASE);
//   motor_4.setSpeed(100);
//   motor_4.run(RELEASE);
// }

// void loop() {
//   motor_1.run(FORWARD);
//   motor_2.run(FORWARD);
//   motor_3.run(FORWARD);
//   motor_4.run(FORWARD);
//   delay(1000);
//   motor_1.run(RELEASE);
//   motor_2.run(RELEASE);
//   motor_3.run(RELEASE);
//   motor_4.run(RELEASE);
//   delay(1000);
// }