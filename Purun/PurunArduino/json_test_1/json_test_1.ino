#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid     = "SSCCWIFI";
const char* password = "2022sscc";

String url = "http://114.71.48.94:8000/api/data";

void setup() {
  Serial.begin(57600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println("start");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("connect");
    WiFiClientSecure client;
    client.setInsecure();
    client.connect(url, 443);
    Serial.println("3");
    HTTPClient https;
    Serial.println("4");
    https.begin(client, url);
    Serial.println("5");
    int httpCode = https.GET();
    if (httpCode > 0)
    {
      
    Serial.println("7");
      String payload = https.getString();
      Serial.println(payload);
    }
    https.end();
  }
  delay(60000);
}