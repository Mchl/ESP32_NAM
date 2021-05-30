#ifndef PARSE_JSON_H
#define PARSE_JSON_H
#include <Arduino.h>
#include <ArduinoJson.h>

struct NamData
{
    int age;
    float PM10count;
    float PM10percentage;
    float PM2_5count;
    float PM2_5percentage;
    float temperature;
    float humidity;
    float pressureRaw;
    float pressureBarometric;
    int signal;
};

NamData parseJson(String jsonString);

#endif