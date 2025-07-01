#include <drivers/api/apiclient.h>
#include <time.h>
#include <chrono>
#include <config.h>
#include <cstdio>
#include <ArduinoJson.h>
#include <Arduino.h>

const int prayerTimeSize = 8;

typedef struct prayerTimes {
    char fajr[prayerTimeSize];
    char dhuhr[prayerTimeSize];
    char asr[prayerTimeSize];
    char maghreb[prayerTimeSize];
    char isha[prayerTimeSize];
    char shuruq[prayerTimeSize];
};

ApiClient& api = ApiClient::getInstance();

char url[128];

void init() {
    sprintf(url, "https://mrie.dev/api/v2/prayertimes/%d", MASJID_ID);
}

prayerTimes getTimes() {
    String response;
    prayerTimes times = {};

    if (api.get(url, response)) {
        StaticJsonDocument<512> doc;
        DeserializationError error = deserializeJson(doc, response);
        if (error) {
            Serial.println("err deserializing json");
            return times;
        }

        strncpy(times.fajr, doc["fajr"] | "", sizeof(times.fajr));
        strncpy(times.dhuhr, doc["dhuhr"] | "", sizeof(times.dhuhr));
        strncpy(times.asr, doc["asr"] | "", sizeof(times.asr));
        strncpy(times.maghreb, doc["maghreb"] | "", sizeof(times.maghreb));
        strncpy(times.isha, doc["isha"] | "", sizeof(times.isha));
        strncpy(times.shuruq, doc["shuruq"] | "", sizeof(times.shuruq));
    } else {
        Serial.println("err getting from mawaqit api @ mrie.dev");
    }

    return times;
}