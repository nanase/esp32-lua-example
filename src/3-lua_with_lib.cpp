#ifdef EXAMPLE3

#include <Arduino.h>
#include <M5Stack.h>
#undef min

extern "C" {
int lua_writestring(char* s) {
  printf(s);
  return 0;
}

int lua_writestringerror(char* s) {
  printf(s);
  return 0;
}

int l_system(const char* cmd) {
  return 0;
}

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

int l_add(lua_State* L) {
  int a = lua_tointeger(L, 1);
  int b = lua_tointeger(L, 2);
  lua_pushinteger(L, a + b);
  return 1;
}

int l_print(lua_State* L) {
  const char* s = lua_tostring(L, 1);
  Serial.println(s);
  return 0;
}

void runLuaScript(lua_State* L, const char* script) {
  if (luaL_dostring(L, script) != LUA_OK) {
    fprintf(stderr, "Lua error: %s\n", lua_tostring(L, -1));
    lua_pop(L, 1);
  }
}

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Speaker.begin();
  M5.Speaker.mute();
  Serial.begin(115200);

  lua_State* L = luaL_newstate();
  luaL_openlibs(L);
  lua_register(L, "add", l_add);
  lua_register(L, "print", l_print);

  runLuaScript(L, R"(
    function mul(a, b)
      return a * b
    end
    print("Hello Lua!")
  )");

  lua_getglobal(L, "mul");
  lua_pushinteger(L, 4);
  lua_pushinteger(L, 5);

  if (lua_pcall(L, 2, 1, 0) == LUA_OK && lua_isinteger(L, -1)) {
    printf("ret=%d\n", lua_tointeger(L, -1));
  } else {
    fprintf(stderr, "cannot exec mul. %s\n", lua_tostring(L, -1));
  }

  lua_pop(L, 1);
  lua_close(L);
}

void loop() {}

#endif
