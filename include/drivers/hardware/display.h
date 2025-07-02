#pragma once

#include <Arduino.h>
#include <drivers/api/mawaqit.h>


void initDisplay();
void showPrayerTimes(const prayerTimes& times, String currentTime);
void showAlarm(String timeStr);