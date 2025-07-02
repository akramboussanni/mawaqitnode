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

void showPrayerTimes(const prayerTimes& times, String currentTime) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.printf("Fajr:    %s\n", times.fajr.c_str());
  display.printf("Shuruq:  %s\n", times.shuruq.c_str());
  display.printf("Dhuhr:   %s\n", times.dhuhr.c_str());
  display.printf("Asr:     %s\n", times.asr.c_str());
  display.printf("Maghreb: %s\n", times.maghreb.c_str());
  display.printf("Isha:    %s\n", times.isha.c_str());

  // Show current time at bottom (assume 64px height, 8px text size)
  display.setCursor(0, SCREEN_HEIGHT - 8);
  display.print(currentTime.c_str());

  display.display();
}

void showAlarm(String timeStr) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(timeStr.c_str(), 0, 0, &x1, &y1, &w, &h);

  int16_t xCentered = (SCREEN_WIDTH - w) / 2;
  display.setCursor(xCentered, 0);
  display.print(timeStr.c_str());

  const char* msg = "Prayer Time";
  display.setTextSize(3);
  display.getTextBounds(msg, 0, 0, &x1, &y1, &w, &h);
  xCentered = (SCREEN_WIDTH - w) / 2;
  int16_t yPos = h + 10; 

  display.setCursor(xCentered, yPos);
  display.print(msg);

  display.display();
}
