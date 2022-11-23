void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
}

void loop() {
  int level = analogRead(A0);
  Serial.println(level);
  if(level <= 500) {
    digitalWrite(8, HIGH);
    Serial.println("ON");
  }
  else {
    digitalWrite(8,LOW);
    Serial.println("OFF");
    delay(1000);
  }w
}