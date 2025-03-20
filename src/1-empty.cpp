#ifdef EXAMPLE1

#include <Arduino.h>
#include <M5Stack.h>
#undef min

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Speaker.begin();
  M5.Speaker.mute();
  Serial.begin(115200);
}

void loop() {}

#endif
