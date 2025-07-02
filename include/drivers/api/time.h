#pragma once

#include <Arduino.h>
#include <ezTime.h>

extern String tzName;
extern Timezone tz;

void initTime();
String getTime();
String getFullTime();
String getTimezone();
time_t parseIso8601(const String& iso);
void localizeTime(const time_t& time, char* outBuf, size_t len);
