// DS 온도 라이브러리 추가 (수온 센서)
#include <OneWire.h>
#include <DallasTemperature.h>

// DS18B20 디지털 2번핀 (수위 센서)
#define TEMP_18B20 2

// 라이브러리 호출 방식에 따라 호출  (수온 센서)
OneWire oneWire(TEMP_18B20);
DallasTemperature sensors(&oneWire);

// PH 센서
#define Vref 4.95
unsigned long int avgValue;     //Store the average value of the sensor feedback
int i=0;
int ph_int;
float ph_float;
float PH_LEVEL;

// LED바
int led_pin = 7;
int LED_STATUS = 1;

// 라즈베리파이 시리얼 통신 정보 저장 변수
char cmd;



// 수위센서 안정화 코드
void average(float sensor_data) {
  float sensorValue;
  long sensorSum;
  int buf[10];                //buffer for read a nalog
  for(int i=0;i<10;i++) {       //Get 10 sample value from the sensor for smooth the value 
    buf[i]=k;//Connect the PH Sensor to A0 port
    delay(10);
  }
  for(int i=0;i<9;i++) {        //sort the analog from small to large
    for(int j=i+1;j<10;j++) {
      if(buf[i]>buf[j]) { 
        int temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }

  avgValue=0;
  for(int i=2;i<8;i++) {                     //take the average value of 6 center sample
  avgValue+=buf[i];
  }
  sensorValue =   avgValue/6;
  Serial.print(sensorValue);
  Serial.println(" ");
}



void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);  // 8번 핀
  pinMode(8, OUTPUT);
  pinMode(A2, INPUT);
  pinMode(A4, OUTPUT);
  digitalWrite(led_pin,HIGH);
}

void loop() {
  sensors.requestTemperatures();  // 센서 값을 읽음(다수개의 DS18B20 연결 가능)
  float temp = sensors.getTempCByIndex(0);  // 첫번째 DS18B20의 온도를 가져옴

  int level = analogRead(A0);  // 수위 가져오기

  float ph = (8 + (random(1,5)-2)*0.12 - 1.0);
  Serial.print(temp);
  Serial.print("/");
  Serial.print(level);
  Serial.print("/");
  Serial.println(ph);
  if(level <= 400) {
    digitalWrite(8, HIGH);
    //Serial.println("PUMP ON");
  } else {
    digitalWrite(8,LOW);
    // Serial.println("PUMP OFF");
    delay(1000);
  }
  if(Serial.available()) {
    cmd = Serial.read();
  } 
  if(cmd=='a') {
    if (LED_STATUS == 1) {
      digitalWrite(led_pin, LOW);
      LED_STATUS == 0;
    } else if (LED_STATUS == 0) {
      digitalWrite(led_pin, HIGH);
      LED_STATUS == 1;
    } 
   /*else if(cmd == 'ba') {
    Serial.println('c');  // led off, feed on
  } else {
    Serial.println('bb');  // led off, feed off
  }*/
  //Serial.println(); Serial.println("============================="); Serial.println();
  }
}