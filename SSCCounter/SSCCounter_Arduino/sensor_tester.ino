#include <DHT.h>
#define DHTPIN A0     // 온습도 센서 핀은 A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int count_sec = 0;
char count[600];
long start_time = 0; // 시간에 따른 기계 제어를 위한 변수

char Airinform;     // 동방 공기질 상태 변수
int Dust = 0;

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

//미세먼지값 측정을 위한 데이터값 변수 선언
float Vo_value = 0;
float Voltage = 0;
float a = 0;

//취합한 정보를 담을 포인터배열 선언  d/t/h/i 순
char* data[60];
int data_arr[4];
char* printdata[4];
int count_rough = 0;

// 시리얼통신으로 취합한 정보 제공하는 함수 
void printData(char* arr[4]) {
    Serial.println("== info start==");
    for (int i = 0; i < 4; i++) {
        Serial.println(arr[i]);
    }
    Serial.println("== info end==");
}
int* get_data() {
    static int rough_data[4];
    //온습도 측정
    int t = dht.readTemperature();
    int h = dht.readHumidity();
    //미세먼지 측정
    digitalWrite(V_LED, LOW);
    delayMicroseconds(280);
    Vo_value = analogRead(Vo);
    delayMicroseconds(40);
    digitalWrite(V_LED, HIGH);
    delayMicroseconds(9680);
    Voltage = Vo_value * 5.0 / 1024.0;
    //조도 측정
    int cds = analogRead(cds_pin);          // 미완성

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

    }
    else if (Dust > 80) {   //미세먼지 농도 나쁨, 빨간불, 팬 동작

    }
    //실험 후 바꿔야 할 부분

    // 취합데이터 배열에 담기
    rough_data[0] = Dust;
    rough_data[1] = t;
    rough_data[2] = h;
    rough_data[3] = cds;
    char a[30],b[30],c[30],d[30];
    sprintf(a," dust= %02d",Dust);
    Serial.print(a);
    sprintf(b," tem = %02d",t);
    Serial.print(b);
    sprintf(c," humi = %02d",h);
    Serial.print(c);
    sprintf(d," cds = %02d",cds);
    Serial.println(d);
    return rough_data;  //1차원 배열로 반환
}
void get_stable(int *rough[60]) {  // 동방 상태 데이터 안정화 코드... 60개 평균

    for (int i = 0; i < 4; i++) {
        int tem = 0;
        for (int j = 0; j < 60; j++) {
            tem += rough[j][i];
        }
        data_arr[i] = tem / 60;
    }
    sprintf(TEM, "%02d", data_arr[0]);
    sprintf(DUST, "%03d", data_arr[1]);
    sprintf(HUMI, "%02d", data_arr[2]);
    sprintf(LIGHT, "%03d", data_arr[3]);
    printdata[0] = TEM;
    printdata[1] = DUST;
    printdata[2] = HUMI;
    printdata[3] = LIGHT;
}
void setup() {
    Serial.begin(9600);
    
}

void loop() {

      // 아두이노 시작 시점 설정..약 50일 후 오버플로우

    unsigned long current_time = millis();
    int *rough_set[60];
    if (current_time - start_time >= 1000) {  //1초 간격으로 동방 상태 점검
        start_time = current_time;
        if (count_rough == 59) {
            get_stable(rough_set);
            printData(printdata);
            count_rough = 0;
        }
        rough_set[count_rough] = get_data();
        count_rough += 1;    
        count_sec++;
    }
    

}
