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
String addOneMinute(const String& timeStr) {
    int hour = timeStr.substring(0, 2).toInt();
    int minute = timeStr.substring(3, 5).toInt();

    minute += 1;
    if (minute >= 60) {
        minute = 0;
        hour = (hour + 1) % 24;
    }

    char buf[6];
    sprintf(buf, "%02d:%02d", hour, minute);
    return String(buf);
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

        Serial.println(parseIso8601(doc["fajr"] | ""));

        times.fajr    = localizeTime(parseIso8601(doc["fajr"] | ""));
        times.dhuhr   = localizeTime(parseIso8601(doc["dhuhr"] | ""));
        times.asr     = localizeTime(parseIso8601(doc["asr"] | ""));
        times.maghreb = localizeTime(parseIso8601(doc["maghreb"] | ""));
        times.isha    = localizeTime(parseIso8601(doc["isha"] | ""));
        times.shuruq  = localizeTime(parseIso8601(doc["shuruq"] | ""));
    } else {
        Serial.print("err getting from mawaqit api @ ");
        Serial.println(url);
    }

    return times;
}

bool isPrayerTime(String current, const prayerTimes& times) {
    return (current == times.fajr) ||
           (current == times.dhuhr) ||
           (current == times.asr) ||
           (current == times.maghreb) ||
           (current == times.isha);
}
