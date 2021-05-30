#include <Arduino.h>
#include "network.h"

void setup() {
  Serial.begin(115200);
  setupWiFi();
}

void loop() {
  static bool wait = false;
  String dataFromNam = getDataFromNAM();
  if (dataFromNam == "") {
    delay(1000);
    return;
  }

  Serial.println(dataFromNam);

  if (wait) {
    delay(5000); // execute once every 5 seconds, don't flood remote service
  }
  wait = true;
}