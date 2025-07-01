#ifndef PRAYERTIMES_H
#define PRAYERTIMES_H

#include <drivers/api/apiclient.h>
#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct prayerTimes {
    char fajr[16];
    char dhuhr[16];
    char asr[16];
    char maghreb[16];
    char isha[16];
    char shuruq[16];
} prayerTimes;

extern ApiClient& api;
extern char url[128];

void init();
prayerTimes getTimes();

#ifdef __cplusplus
}
#endif

#endif
