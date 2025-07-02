#ifndef MAWAQIT_H
#define MAWAQIT_H

#include <Arduino.h>

static const int prayerTimeSize = 6;

typedef struct prayerTimes {
    char fajr[prayerTimeSize];
    char dhuhr[prayerTimeSize];
    char asr[prayerTimeSize];
    char maghreb[prayerTimeSize];
    char isha[prayerTimeSize];
    char shuruq[prayerTimeSize];
} prayerTimes;

void initMawaqit();
prayerTimes getPrayerTimes();

#endif
