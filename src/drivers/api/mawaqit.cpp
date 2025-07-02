#include "drivers/api/mawaqit.h"
#include <drivers/api/apiclient.h>
#include <drivers/api/time.h>
#include <chrono>
#include <config.h>
#include <cstdio>
#include <ArduinoJson.h>
#include <Arduino.h>

char url[128];

void initMawaqit() {
    sprintf(url, "https://mrie.dev/api/v2/prayertimes/%s", MASJID_ID);
}

prayerTimes getPrayerTimes() {
    String response;
    prayerTimes times = {};

    if (ApiClient::getInstance().get(url, response)) {
        StaticJsonDocument<512> doc;
        DeserializationError error = deserializeJson(doc, response);
        if (error) {
            Serial.println("err deserializing json");
            return times;
        }
        
        localizeTime(parseIso8601(doc["fajr"] | ""), times.fajr, sizeof(times.fajr));
        localizeTime(parseIso8601(doc["dhuhr"] | ""), times.dhuhr, sizeof(times.dhuhr));
        localizeTime(parseIso8601(doc["asr"] | ""), times.asr, sizeof(times.asr));
        localizeTime(parseIso8601(doc["maghreb"] | ""), times.maghreb, sizeof(times.maghreb));
        localizeTime(parseIso8601(doc["isha"] | ""), times.isha, sizeof(times.isha));
        localizeTime(parseIso8601(doc["shuruq"] | ""), times.shuruq, sizeof(times.shuruq));
    } else {
        Serial.print("err getting from mawaqit api @ ");
        Serial.println(url);
    }

    return times;
}