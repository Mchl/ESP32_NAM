#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMono9pt7b.h>

#include "GxEPD2_display_selection_new_style.h"
#include "network.h"
#include "parse_json.h"


void setup() {
  Serial.begin(115200);
  setupWiFi();
  display.init();
  display.setRotation(1);
  display.setFont(&FreeMono9pt7b);
  display.setTextColor(GxEPD_BLACK);

}

void loop() {
  static bool wait = false;
  String dataFromNam = getDataFromNAM();
  if (dataFromNam == "") {
    delay(1000);
    return;
  }

  NamData namData = parseJson(dataFromNam);

  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(0, 35);
    display.print(String("  PM 10: ") + namData.PM10percentage + String("%\n"));
    display.print(String(" PM 2.5: ") + namData.PM2_5percentage + String("%\n"));
    display.print(String("   Temp: ") + namData.temperature + String("C\n"));
    display.print(String("    Hum: ") + namData.humidity + String("%\n"));
    display.print(String("   Pres: ") + namData.pressureBarometric + String("hPa"));
  } while (display.nextPage());
  display.hibernate();

  if (wait) {
    delay(5000); // execute once every 5 seconds, don't flood remote service
  }
  wait = true;
}