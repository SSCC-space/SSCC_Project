#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

char cmd;
float TEMP = 21.03;
float PH = 7.32;
int WATER_LEVEL = 433;

void setup() {
  Serial.begin(57600);
  WiFi.begin("SSCCWIFI", "2022sscc");   // WiFi 연결
  while (WiFi.status() != WL_CONNECTED) {  // WiFi 연결 대기
    delay(500);
    Serial.println("Waiting for connection");
  }
}

void post_json(float TEMP, float PH, int WATER_LEVEL) {
  if (WiFi.status() == WL_CONNECTED) { // WiFi 연결 상태 확인
    StaticJsonDocument<100> testDocument;
    testDocument["TEMP"] = TEMP;
    testDocument["PH"] = PH;
    testDocument["WATER_LEVEL"] = WATER_LEVEL;
    char buffer[100];
    serializeJson(testDocument, buffer);
    Serial.println(buffer);
    WiFiClient client;
    HTTPClient http;    //Declare object of class HTTPClient
    http.begin(client, "http://114.71.48.94:8000/api/data");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
    int httpCode = http.POST(buffer);   //Send the request                                 //Get the response payload
    Serial.println(httpCode);   //Print HTTP return code
    //String payload = http.getString();       
    //Serial.println(payload);    //Print request response payload
    http.end();  //Close connection
  }
  else {
    Serial.println("Error in WiFi connection");
  }
}

void get_json() {
  if(Serial.available()){
    cmd = Serial.read();
  }
  if(cmd=='aa') {
    Serial.println('a');  // led on, feed on
  } else if(cmd == 'ab') {
    Serial.println('b');  // led on, feed off
  } else if(cmd == 'ba') {
    Serial.println('c');  // led off, feed on
  } else {
    Serial.println('bb');  // led off, feed off
  }
}

void loop() {
  get_json();
  float TEMP = 21.03;
  float PH = 7.32;
  int temp = TEMP*100; float temperature = temp/100;
  int ph = PH*100; float ph_level = ph/100;
  int WATER_LEVEL = 433;
  post_json(temperature, ph_level, WATER_LEVEL);
  
  delay(10000);
}
