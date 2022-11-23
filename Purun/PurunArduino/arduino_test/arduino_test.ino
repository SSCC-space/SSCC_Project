#include <OneWire.h>
#include <DallasTemperature.h>

#define water_temperature_pin 2
#define OFFMODE 0
#define FN 1
#define FF 2

char cmd;
int state = OFFMODE;

OneWire onWire(water_temperature_pin)
DAlaasTemperature sensors(&onewire)

void setup() {
  sensors.begin();
  Serial.begin(9600);
  pinMode(12, OUTPUT);
}

void loop() {
  int water_level = random(0,700);
  sensors.requestTemperatures();
  float water_temperature = snesors.getTempCByIndex(0);

  if(Serial.available()){
  cmd = Serial.read();
  }
  if(cmd=='a'){
    state=FN;
  }else if(cmd=='b'){
    state=FF;
  }else{
    state=OFFMODE;
  }

  //모터 정회전(180도)
  if(state == FN){
    digitalWrite(12, HIGH);
    Serial.print("Feed: on,    ");
  }
  
  else{
  state=OFFMODE;
  }

  if (state == OFFMODE) {
    digitalWrite(12, LOW);
    Serial.print("Feed: off,    ");
  }
  state=OFFMODE;
  Serial.print("water_level: ");
  Serial.print(water_level);
  Serial.print("|water_temp: ");
  Serial.print(water_temperature);

  delay(50);
}