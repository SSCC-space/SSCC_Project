// DS 온도 라이브러리 추가
#include <OneWire.h>
#include <DallasTemperature.h>

// DS18B20 디지털 2번핀
#define TEMP_18B20 2

// 라이브러리 호출 방식에 따라 호출
OneWire oneWire(TEMP_18B20);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // 센서 값을 읽음(다수개의 DS18B20 연결 가능)
  sensors.requestTemperatures();
  // 첫번째 DS18B20의 온도를 가져옴
  float temp_18b20 = sensors.getTempCByIndex(0);
  Serial.print("DS18B20: "); Serial.println(temp_18b20);
  delay(1000);
}