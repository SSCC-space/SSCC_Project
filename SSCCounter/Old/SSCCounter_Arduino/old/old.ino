#include <DHT.h>
#define DHTPIN A0     // 온습도 센서 핀은 A0
#define DHTTYPE DHT11
#include<Servo.h> //Servo 라이브러리를 추가
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
Servo f_servo;      //Servo 클래스로 servo객체 생성
Servo s_servo;
int f_value = 0;    // 각도를 조절할 변수 value
int s_value = 0;
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3F,16,2);


//시리얼로 보낼 동방 상태값
char DUST[10];  // 미세먼지
char TEM[10];   // 온도
char HUMI[10];  // 습도
char LIGHT[10]; // 조도

int Vo = A14;   // 미세먼지 빛 수신부 센서 핀은 A14
int V_LED = 50;  // 미세먼지 빛 송신부 핀은 D50
int FAN = 5;     // 5v 릴레이 신호 핀은 D49
int R_LED = 22;  // 이하 led 인디케이터 핀은 각각 R: 22 G 24 B 26
int Y_LED = 24;
int G_LED = 26;
int cds_pin = A12; // 조도 센서 핀은 A12
int f_mot = 6;
int s_mot = 7;
int m_count = 0;

//미세먼지값 측정을 위한 데이터값 변수 선언
float Vo_value = 0;
float Voltage = 0;
float a = 0;

// 데이터
int Dust;
int t;
int h;
int cds;
int sum[4] = {0,0,0,0};

int count_rough = 0;
int motor_time = 0;

void move_motor(){
    f_value = 0;
    s_value = 0;
    switch(m_count){
      case 0:
        f_servo.write(20);                       //  #### 모터 각도 조정..여기를 15도로 바꾼다면 아래는 -15도로 바꿔주기
        //s_servo.write(0);
        break;
      case 1:
        f_servo.write(0);
        //s_servo.write(0);
        break;
      case 2:
        f_servo.write(-20);                      //  #### 모터 각도 조정
        //s_servo.write(20);
        break;
      case 3:
        f_servo.write(0);
        //s_servo.write(20);
        break;
    }
    m_count = (m_count + 1) % 4;
}

void get_data() {
    Dust = 0;
    //온습도 측정
    t = dht.readTemperature();
    h = dht.readHumidity();
    //미세먼지 측정
    digitalWrite(V_LED, LOW);
    delayMicroseconds(280);
    Vo_value = analogRead(Vo);
    delayMicroseconds(40);
    digitalWrite(V_LED, HIGH);
    delayMicroseconds(9680);
    Voltage = Vo_value * 5.0 / 1024.0;
    //조도 측정
    cds = analogRead(cds_pin);          // 

    if (Voltage < 0.1) {
        Dust = 0;
    }
    else if (Voltage < 0.8) {
        Dust = 10 * (5 * (Voltage - 0.1));
    }
    else if (Voltage < 1) {
        Dust = 10 + 15 * ((Voltage - 0.8) * 10);
    }
    else if (Voltage > 1) {
        Dust = 40 + 16 * ((Voltage - 1) * 10);
    }
    delay(500);
    if (Dust < 50) {   //미세먼지 농도 좋음, 초록불, 팬 정지
        digitalWrite(FAN, LOW);
        digitalWrite(R_LED, LOW);
        digitalWrite(Y_LED, LOW);
        digitalWrite(G_LED, HIGH);
    }
    else if (Dust < 80) {   //미세먼지 농도 보통, 노란불, 팬 동작
        digitalWrite(FAN, HIGH);
        digitalWrite(R_LED, LOW);
        digitalWrite(Y_LED, HIGH);
        digitalWrite(G_LED, LOW);

    }
    else if (Dust > 80) {   //미세먼지 농도 나쁨, 빨간불, 팬 동작
        digitalWrite(FAN, HIGH);
        digitalWrite(R_LED, HIGH);
        digitalWrite(Y_LED, LOW);
        digitalWrite(G_LED, LOW);

    }
    /*
// ==== 디버깅용  최종단계에서 지워야함
    char a[30],b[30],c[30],d[30];
    sprintf(a," dust= %02d",Dust);
    Serial.print(a);
    sprintf(b," tem = %02d",t);
    Serial.print(b);
    sprintf(c," humi = %02d",h);
    Serial.print(c);
    sprintf(d," cds = %02d",cds);
    Serial.println(d);
    */
}

void setup() {
    f_servo.attach(f_mot);
    s_servo.attach(s_mot);
    Serial.begin(9600);
    int sum[4] = {0,0,0,0};
    Serial.println("serial begin");
    
    lcd.begin();                  
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("SSCC Indicator");
    lcd.setCursor(0,1);   
}

void loop() {

    if (count_rough == 5) {
            for(int i=0; i<4; i++){
                char info[30];
                sprintf(info,"%3d/",sum[i]/4);
                Serial.print(info);
            }
            char lcdprint[50];
            lcd.clear();
            lcd.print("SSCC condition");
            lcd.setCursor(0,1);
            sprintf(lcdprint,"tem:%d, humi:%d",sum[1]/4,sum[2]/4);
            lcd.print(lcdprint);
            Serial.print("\n");
            for(int i=0; i<4; i++){
                sum[i] = 0;
            }
            
            count_rough = 0;
        }
    else{
        get_data();
        delay(800);          // 나중에 800 으로 수정
        sum[0] += Dust;
        sum[1] += t;+
        sum[2] += h;
        sum[3] += cds;
/*
        for (int i =0; i<4; i++){
          char tem[20];
          sprintf(tem,"%d ",sum[i]);
          Serial.print(tem);          
        }
        Serial.print("\n"); */
    }
    
    count_rough += 1;
    motor_time += 1;
    if (motor_time == 20){
      move_motor();
      motor_time =0;
    }
    

}
