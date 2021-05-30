#include <Arduino.h>
#include "network.h"
#include "parse_json.h"

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

  NamData namData = parseJson(dataFromNam);

  Serial.printf(
      "PM 10: %.1f%%  PM 2.5: %.1f%%  Temperature: %.1f °C  Pressure: %.1f hPa  Humidity: %.1f%%  Signal: %d dBm \n",
      namData.PM10percentage,
      namData.PM2_5percentage,
      namData.temperature,
      namData.pressureBarometric,
      namData.humidity,
      namData.signal);

  if (wait) {
    delay(5000); // execute once every 5 seconds, don't flood remote service
  }
  wait = true;
}