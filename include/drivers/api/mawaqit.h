#ifndef MAWAQIT_H
#define MAWAQIT_H

#include <Arduino.h>

typedef struct prayerTimes {
    String fajr    = "";
    String dhuhr   = "";
    String asr     = "";
    String maghreb = "";
    String isha    = "";
    String shuruq  = "";
} prayerTimes;


void initMawaqit();
prayerTimes getPrayerTimes();
bool isPrayerTime(String current, const prayerTimes& times);

#endif
