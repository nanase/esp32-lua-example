#ifdef EXAMPLE5

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
  lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::coroutine, sol::lib::table, sol::lib::io,
                     sol::lib::os, sol::lib::string, sol::lib::math, sol::lib::utf8, sol::lib::debug);

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
