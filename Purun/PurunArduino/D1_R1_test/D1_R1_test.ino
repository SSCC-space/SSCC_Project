#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
 
void setup() {
 
  Serial.begin(57600);                            //Serial connection
  WiFi.begin("SSCCWIFI", "2022sscc");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status


    DynamicJsonDocument doc(2048);
//    StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
//    JsonObject& JSONencoder = JSONbuffer.createObject();
    float temp = 1.10;
    float PH = 1.01;
    //int WATER_LEVEL = 534;
    //int LED
    //doc["TEMP"] = temp;
    //doc["PH"] = PH;
    //WATER_LEVEL, LED, FEED
    //JSONencoder["TestType"] = "TEMP, PH, WATER_LEVEL, LED, FEED";

    // char JSONmessageBuffer[300];
    // JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    // Serial.println(JSONmessageBuffer);
    String json;
    serializeJson({"TEMP": 1.1, "PH": 2.1}, json);
    Serial.println(json);
    WiFiClient client;
    HTTPClient http;    //Declare object of class HTTPClient
 
    http.begin(client, "http://114.71.48.94:8000/api/data");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
    int httpCode = http.POST(json);   //Send the request
    String payload = http.getString();                                        //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
 
    http.end();  //Close connection
 
  } else {
 
    Serial.println("Error in WiFi connection");
 
  }
 
  delay(10000);  //Send a request every 30 seconds
 
}
