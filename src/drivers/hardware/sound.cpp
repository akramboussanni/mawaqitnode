#include <Arduino.h>
#include <config.h>

void initSpeaker() {
    ledcSetup(0, 2000, 8);
    ledcAttachPin(SPEAKER_PIN, 0);
}

void playSound() {
  const int melody[] = { 440, 494, 523, 440, 0 }; 
  const int noteDuration = 300;

  for (int i = 0; melody[i] != 0; i++) {
    ledcWriteTone(0, melody[i]);
    delay(noteDuration);
  }

  ledcWriteTone(0, 0);
}