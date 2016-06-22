#include <Ultrasonic.h>

Ultrasonic sensor(2, 3);

void setup() {
  Serial.begin(9600);
}

void loop() {
  long us = sensor.timing();
  int cm = sensor.convert(us, Ultrasonic::CM);
  if (cm > 255) {
    cm = 0;
  }
  Serial.write(cm);
  delay(10);
}
