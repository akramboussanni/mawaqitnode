#include "drivers/api/time.h"
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <drivers/api/apiclient.h>
#include <ezTime.h>
#include <time.h>

Timezone tz;

void initTime() {
    waitForSync();
    tz.setLocation(getTimezone());
    tz.setDefault();
}

bool isMidnight() {
    return tz.hour() == 0;
}

String getTime() {
    return tz.dateTime("H:i");
}

String getTimezone() {
    String response;
    if (ApiClient::getInstance().get("https://worldtimeapi.org/api/ip", response)) {
        StaticJsonDocument<2048> doc;
        DeserializationError error = deserializeJson(doc, response);

        if (error) {
            Serial.println("err while deserializing tz info");
            Serial.print("response: ");
            Serial.println(response);
            return "";
        }

        return doc["timezone"];
    }

    Serial.println("err while fetching tz info");
    return "";
}

time_t parseIso8601(const String& iso) {
  int year = iso.substring(0,4).toInt();
  int month = iso.substring(5,7).toInt();
  int day = iso.substring(8,10).toInt();
  int hour = iso.substring(11,13).toInt();
  int minute = iso.substring(14,16).toInt();
  int second = iso.length() > 16 ? iso.substring(17,19).toInt() : 0;

  tmElements_t tm;
  tm.Year = year - 1970;
  tm.Month = month;
  tm.Day = day;
  tm.Hour = hour;
  tm.Minute = minute;
  tm.Second = second;
  
  return makeTime(tm);
}

String localizeTime(const time_t& time) {
    //time_t local = tz.tzTime(time, UTC_TIME);
    int h = hour(time, UTC_TIME);
    int m = minute(time, UTC_TIME);
    String s;
    s.reserve(5);  // preallocate to avoid reallocations
    s += (h < 10) ? '0' : char('0' + h / 10);
    s += char('0' + h % 10);
    s += ':';
    s += (m < 10) ? '0' : char('0' + m / 10);
    s += char('0' + m % 10);
    return s;
}