#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <drivers/api/mawaqit.h>


extern void initDisplay();
extern void showPrayerTimes(const prayerTimes& times, const char* currentTime);
#endif