#ifdef EXAMPLE4

#include <Arduino.h>
#include <M5Stack.h>
#undef min

#include "sol/sol.hpp"

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Speaker.begin();
  M5.Speaker.mute();
  Serial.begin(115200);

  sol::state lua;

  lua["add"]   = [](int a, int b) { return a + b; };
  lua["print"] = [](const char* s) { Serial.println(s); };

  lua.script(R"(
     function mul(a, b)
       return a * b
     end
     print("Hello Lua!")
  )");

  int ret = lua["mul"](4, 5);
  printf("ret=%d\n", ret);
}

void loop() {}

#endif
