#include <Arduino.h>
#include "network.h"
#include "parse_json.h"
#include "display.h"


void setup() {
  Serial.begin(115200);
  setupWiFi();
  setupDisplay();
}

void loop() {
  static bool wait = false;
  String dataFromNam = getDataFromNAM();
  if (dataFromNam == "") {
    delay(1000);
    return;
  }

  NamData namData = parseJson(dataFromNam);

  displayNamData(namData);

  if (wait) {
    delay(5000); // execute once every 5 seconds, don't flood remote service
  }
  wait = true;
}