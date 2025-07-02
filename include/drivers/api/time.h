#pragma once

#include <Arduino.h>
#include <ezTime.h>

extern String tzName;
extern Timezone tz;

void initTime();
bool isMidnight();
String getTime();
String getTimezone();
time_t parseIso8601(const String& iso);
String localizeTime(const time_t& time);
