void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.write(map(analogRead(A0), 0, 200, 0, 255)); 
  delay(10);
}
