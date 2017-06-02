void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int dado = Serial.read();

    if (dado == '0') {
      digitalWrite(7, LOW);
    } else {
      digitalWrite(7, HIGH);
    }
  }
  
  delay(10);
}
