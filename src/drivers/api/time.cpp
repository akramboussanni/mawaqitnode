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
    tz.setLocation(getTimezone());
}

String getTime() {
    return tz.dateTime("H:i");
}

String getFullTime() {
    return tz.dateTime("H:i:s");
}

String getTimezone() {
    String response;
    if (ApiClient::getInstance().get("http://worldtimeapi.org/api/ip", response)) {
        StaticJsonDocument<512> doc;
        DeserializationError error = deserializeJson(doc, response);

        if (error) {
            return "err while deserializing tz info";
        }

        return doc["timezone"];
    }

    return "err while fetching tz info";
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

void localizeTime(const time_t& time, char* outBuf, size_t len) {
    time_t local = tz.tzTime(time);
    snprintf(outBuf, len, "%02d:%02d", hour(local), minute(local));
}
