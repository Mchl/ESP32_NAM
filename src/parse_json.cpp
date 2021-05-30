#include "parse_json.h"
#include "conf.h"

NamData parseJson(String jsonString)
{
    DynamicJsonDocument jsonDoc(JSONDOC_SIZE);

    DeserializationError err = deserializeJson(jsonDoc, jsonString);

    NamData namData;

    if (err)
    {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(err.c_str());
        Serial.print(F("tried to parse: "));
        Serial.println(jsonString);
        return namData;
    };

    namData.age = jsonDoc["age"];
    namData.PM10count = jsonDoc["sensordatavalues"][0]["value"];
    namData.PM10percentage = namData.PM10count / PM10_NORM * 100;
    namData.PM2_5count = jsonDoc["sensordatavalues"][1]["value"];
    namData.PM2_5percentage = namData.PM2_5count / PM2_5_NORM * 100;
    namData.temperature = jsonDoc["sensordatavalues"][2]["value"];
    namData.humidity = jsonDoc["sensordatavalues"][3]["value"];
    namData.pressureRaw = jsonDoc["sensordatavalues"][4]["value"];
    namData.pressureRaw /= 100;
    namData.pressureBarometric = namData.pressureRaw * pow(1 - (0.0065 * ASL) / (namData.temperature + 0.0065 * ASL), -5.257);
    namData.signal = jsonDoc["sensordatavalues"][10]["value"];

    return namData;
};