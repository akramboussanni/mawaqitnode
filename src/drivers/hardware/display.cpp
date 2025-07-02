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

  display.print("Fajr:    ");
  display.println(times.fajr);
  display.print("Shuruq:  ");
  display.println(times.shuruq);
  display.print("Dhuhr:   ");
  display.println(times.dhuhr);
  display.print("Asr:     ");
  display.println(times.asr);
  display.print("Maghreb: ");
  display.println(times.maghreb);
  display.print("Isha:    ");
  display.println(times.isha);

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

  const char* line1 = "Prayer";
  const char* line2 = "Time";

  display.setTextSize(2);

  int16_t x2, y2;
  uint16_t w2, h2;
  display.getTextBounds(line1, 0, 0, &x2, &y2, &w2, &h2);

  int16_t x3, y3;
  uint16_t w3, h3;
  display.getTextBounds(line2, 0, 0, &x3, &y3, &w3, &h3);

  uint16_t spacing = 4;
  uint16_t totalHeight = h + spacing + h2 + h3 + spacing;

  int16_t yStart = (SCREEN_HEIGHT - totalHeight) / 2;

  display.setTextSize(1);
  int16_t xCentered = (SCREEN_WIDTH - w) / 2;
  display.setCursor(xCentered, yStart);
  display.print(timeStr.c_str());

  xCentered = (SCREEN_WIDTH - w2) / 2;
  display.setTextSize(2);
  display.setCursor(xCentered, yStart + h + spacing);
  display.print(line1);

  xCentered = (SCREEN_WIDTH - w3) / 2;
  display.setCursor(xCentered, yStart + h + spacing + h2);
  display.print(line2);

  display.display();
}
