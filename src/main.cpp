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

void setup() {
  Serial.begin(115200);
  delay(1000);

  connect();

  initTime();
  initMawaqit();
  // Remove the following 2 lines as you wish to disable features.
  initDisplay();
  initSpeaker();

  prayerTimes times = getPrayerTimes();
  minutely();
}

void loop() {
  events();
}


//alarm feature
void minutely() {
  String time = getTime();
  prayerTimes times = getPrayerTimes();

  Serial.println(time);
  if (isPrayerTime(time, times)) {
    showAlarm(time);
    playSound();
  } else {
    showPrayerTimes(times, time);
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
