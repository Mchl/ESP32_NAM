#include <Arduino.h>
#include <WiFi.h>

#include "secrets.h"

void setupWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.setHostname("ESP32_NAM_Display");

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.print(".");
      esp_restart();
  }
  Serial.println(F("WiFi connected"));
  Serial.println("");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  delay(5000);
  setupWiFi();
}

void loop() {
  delay(1000);
  Serial.println("BLINK");
}