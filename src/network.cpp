#include <network.h>
#include <WiFi.h>
#include "secrets.h"

IPAddress namServer(192, 168, 1, 38);

void setupWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    WiFi.setHostname("ESP32_NAM_Display");

    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.print(".");
        esp_restart();
    }
    Serial.println(F("WiFi connected"));
    Serial.println("");
    Serial.println(WiFi.localIP());
}

String getDataFromNAM()
{
    char status[32] = {0};
    WiFiClient http;

    if (!http.connect(namServer, 80))
    {
        Serial.println("HTTP client connection failed");
        return "";
    }

    if (http.connected())
    {
        Serial.println("HTTP client connected");
        http.println("GET /data.json HTTP/1.0");
    }

    // wait for data to be available
    unsigned long timeout = millis();
    while (http.available() == 0)
    {
        if (millis() - timeout > 30000)
        {
            Serial.println("HTTP client Timeout !");
            http.stop();
            return "";
        }
    }
    Serial.printf("HTTP client waited for response %lu milliseconds \n", millis() - timeout);

    http.readBytesUntil('\r', status, sizeof(status));

    if (strcmp(status, "HTTP/1.0 200 OK") != 0)
    {
        Serial.print("Unexpected response: ");
        Serial.println(status);
        http.stop();
        return "";
    }

    // Skip HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
    if (!http.find(endOfHeaders))
    {
        Serial.println("Invalid response");
        http.stop();
        return "";
    }

    String result = "";
    while (http.available())
    {
        char c = http.read();
        result.concat(c);
    }

    http.stop();
    return result;
}