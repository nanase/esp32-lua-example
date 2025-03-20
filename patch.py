Import("env") # type: ignore

from pathlib import Path
import os
import shutil
import requests

LUA_DIR = Path("lib/lua")
SOL_DIR = Path("include/sol")
SOL_DIR.mkdir(parents=True, exist_ok=True)

LUACONF_PATH = LUA_DIR / "luaconf.h"
LUACONF_BAK = str(LUACONF_PATH) + ".bak"
ONELUA_PATH = LUA_DIR / "onelua.c"
ONELUA_BAK = LUA_DIR / "onelua.c.bak"
LUA_PATH = LUA_DIR / "lua.c"
LUA_BAK = LUA_DIR / "lua.c.bak"

SOL_FILES = {
    "sol.hpp": "https://github.com/ThePhD/sol2/releases/download/v3.3.0/sol.hpp",
    "forward.hpp": "https://github.com/ThePhD/sol2/releases/download/v3.3.0/forward.hpp",
    "config.hpp": "https://github.com/ThePhD/sol2/releases/download/v3.3.0/config.hpp",
}


def download_files():
    for filename, url in SOL_FILES.items():
        file_path = SOL_DIR / filename
        if not file_path.exists():
            print(f"Downloading {url}...")
            response = requests.get(url, stream=True)
            if response.status_code == 200:
                with open(file_path, "wb") as f:
                    f.write(response.content)
                print(f"Downloaded {filename} successfully.")
            else:
                print(f"Failed to download {filename}: HTTP {response.status_code}")
        else:
            print(f"{filename} already exists, skipping download.")


def before_build():
    download_files()

    with open(LUACONF_PATH, "r") as f:
        content = f.read()

    if "#define LUA_32BITS\t1" not in content:
        patched_content = content.replace("#define LUA_32BITS\t0", "#define LUA_32BITS\t1")
        shutil.copy(LUACONF_PATH, LUACONF_BAK)

        with open(LUACONF_PATH, "w") as f:
            f.write(patched_content)

        print("Applied patch to luaconf.h")
    else:
        print("luaconf.h is already patched")

    if os.path.exists(LUA_PATH):
        shutil.move(LUA_PATH, LUA_BAK)
        print("Renamed lua.c to lua.c.bak")

    if os.path.exists(ONELUA_PATH):
        shutil.move(ONELUA_PATH, ONELUA_BAK)
        print("Renamed onelua.c to onelua.c.bak")


def after_build(source, target, env):
    if os.path.exists(LUACONF_BAK):
        shutil.move(LUACONF_BAK, LUACONF_PATH)
        print("Restored luaconf.h from backup")

    if os.path.exists(LUA_BAK):
        shutil.move(LUA_BAK, LUA_PATH)
        print("Restored lua.c")

    if os.path.exists(ONELUA_BAK):
        shutil.move(ONELUA_BAK, ONELUA_PATH)
        print("Restored onelua.c")


before_build()
env.AddPostAction("$PROGPATH", after_build) # type: ignore
