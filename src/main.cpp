#include <Arduino.h>

int LED_BLINK = 19;

void setup() {
  pinMode(LED_BLINK, OUTPUT);
}

void loop() {
  delay(1000);
  digitalWrite(LED_BLINK, HIGH);
  delay(1000);
  digitalWrite(LED_BLINK, LOW);
}