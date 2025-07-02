#include <Arduino.h>
#include <WiFi.h>
//project specific
#include <config.h>
#include <drivers/api/mawaqit.h>
#include <drivers/api/time.h>
#include <drivers/api/apiclient.h>
#include <drivers/hardware/sound.h>
#include <drivers/hardware/display.h>

void connect();
void hourly();
void minutely();

prayerTimes* times;
void setup() {
  Serial.begin(115200);
  delay(1000);

  connect();

  initTime();
  initMawaqit();
  initDisplay();
  initSpeaker();

  times = getPrayerTimes();
  Serial.println("just fetched, checking now");
  Serial.printf("PrayerTimes fetched:\n fajr: %p '%s'\n shuruq: %p '%s'\n dhuhr: %p '%s'\n",
              times->fajr, times->fajr, times->shuruq, times->shuruq, times->dhuhr, times->dhuhr);
  hourly();
  minutely();
}

void loop() {
  events();
}

//checks for new times
void hourly() {
  if (isMidnight()) {
    times = getPrayerTimes();
  }
  setEvent(hourly, now() + 3600);
}

//alarm feature
void minutely() {
  String time = getTime();
  Serial.println(time);
  if (isPrayerTime(time, *times)) {
    showAlarm(time);
    playSound();
  } else {
    showPrayerTimes(*times, time);
  }
  setEvent(minutely, now() + 60);
}

void connect() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting to wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nwifi connected successfully");
}
