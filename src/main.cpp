#include <Arduino.h>
#include <WiFi.h>
//project specific
#include <config.h>
#include <drivers/api/mawaqit.h>
#include <drivers/api/time.h>
#include <drivers/api/apiclient.h>
#include <drivers/hardware/display.h>

void connect();

void connect() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting to wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nwifi connected successfully");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  connect();

  initTime();
  initMawaqit();
  initDisplay();
}

void loop() {
  showPrayerTimes(getPrayerTimes(), getTime().c_str());
  delay(1000);
}
