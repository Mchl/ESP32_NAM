#include <Arduino.h>
#include <WiFi.h>

#include "secrets.h"

WiFiClient http;
IPAddress namServer(192,168,1,38);

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
  setupWiFi();
}

void loop() {
  char status[32] = {0};

  http.connect(namServer, 80);
  http.println("GET /data.json HTTP/1.0");
  http.println();
  while (!http.available()) {
    delay(10);
  }

  http.readBytesUntil('\r', status, sizeof(status));

  if (strcmp(status, "HTTP/1.0 200 OK") != 0)
  {
    Serial.print("Unexpected response: ");
    Serial.println(status);
    http.stop();
    return;
  }

// Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!http.find(endOfHeaders))
  {
    Serial.println("Invalid response");
    http.stop();
    return;
  }

  while (http.available()) {
    char c = http.read();
    Serial.print(c);
  }
  Serial.println();

  http.stop();
  delay(5000);
}