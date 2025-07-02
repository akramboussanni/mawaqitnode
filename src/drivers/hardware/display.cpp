#include "drivers/hardware/display.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <config.h>


TwoWire displayWire = TwoWire(0);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &displayWire, -1);

void initDisplay() {
  displayWire.begin(SDA_PIN, SCL_PIN);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.display();
}

void showPrayerTimes(const prayerTimes& times, const char* currentTime) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.printf("Fajr:    %s\n", times.fajr);
  display.printf("Shuruq:  %s\n", times.shuruq);
  display.printf("Dhuhr:   %s\n", times.dhuhr);
  display.printf("Asr:     %s\n", times.asr);
  display.printf("Maghreb: %s\n", times.maghreb);
  display.printf("Isha:    %s\n", times.isha);

  // Show current time at bottom (assume 64px height, 8px text size)
  display.setCursor(0, SCREEN_HEIGHT - 8);
  display.print(currentTime);

  display.display();
}

void showAlarm() {
  
}
