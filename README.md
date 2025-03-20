# esp32-lua-example

ESP32 で Lua を使うサンプルプログラムです。

動作確認は M5Stack Basic / Visual Studio Code / PlatformIO で行っています。

## 使い方

サブモジュールも含めてクローンを行ってください。

```sh
$ git clone --recursive git@github.com:nanase/esp32-lua-example.git

# --recursive をつけずにクローンしてしまった場合
$ git clone git@github.com:nanase/esp32-lua-example.git
$ git submodule update --init --recursive
```

### ビルド

[patch.py](./patch.py) によってビルド時に Sol2 のヘッダファイルを自動でダウンロードします。また、Lua のライブラリの一部ファイルの書き換えを行います。

```sh
# 環境を指定してビルド
$ platformio run --environment [環境名]

# すべての環境をビルド
$ platformio run
```

### アップロード

```sh
# 環境を指定してビルド＆アップロード
$ platformio run --target upload --environment [環境名]
```

## 環境

環境によってマクロが定義され、環境名に応じた構成が有効になります。

| 環境名                                     | 構成                            |
| :----------------------------------------- | :------------------------------ |
| [1-empty](src/1-empty.cpp)                 | Lua 未使用                      |
| [2-lua](src/2-lua.cpp)                     | Lua                             |
| [3-lua-with-lib](src/3-lua_with_lib.cpp)   | Lua + Lua 標準ライブラリ        |
| [4-sol2](src/4-sol2.cpp)                   | Lua + Sol2                      |
| [5-sol2-with-lib](src/5-sol2_with_lib.cpp) | Lua + Sol2 + Lua 標準ライブラリ |

## 参考文献（先駆者）

このリポジトリの内容は以下を参考に作られました。

- **lua in arduino-esp32**
  https://github.com/inajob/lua-in-arduino-esp32

## ライセンス

[MIT ライセンス](LICENSE.md)
