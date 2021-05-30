#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

#include "GxEPD2_display_selection_new_style.h"
#include "network.h"
#include "parse_json.h"


void setup() {
  Serial.begin(115200);
  setupWiFi();
  display.init();
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.getTextBounds("Hello, World!", 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print("Hello, World!");
  } while (display.nextPage());
  display.hibernate();
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