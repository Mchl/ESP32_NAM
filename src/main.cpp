#include <Arduino.h>
#include "network.h"
#include "parse_json.h"
#include "display.h"

#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 300        /* Time ESP32 will go to sleep (in seconds) */
RTC_DATA_ATTR int bootCount = 0;

void hush() {
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Going to sleep now");
  delay(1000);
  Serial.flush();
  esp_deep_sleep_start();
}

void setup() {
  Serial.begin(115200);
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  setupWiFi();

  String dataFromNam = getDataFromNAM();
  if (dataFromNam == "")
  {
    hush();
  }
  NamData namData = parseJson(dataFromNam);

  if(namData.signal == 0) {
    hush();
  }

  setupDisplay();
  displayNamData(namData);

  hush();
  Serial.println("This will never be printed");
}

void loop() {

}