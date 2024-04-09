[![en](https://img.shields.io/badge/lang-en-red.svg)](./PluginDependency.md)
[![jp](https://img.shields.io/badge/lang-jp-green.svg)](./PluginDependency.jp.md)

# Used Plugins

## magic_enum

* Source : https://github.com/Neargye/magic_enum
* Version : v0.9.0
* Location in project : [here](../lib/magic_enum.hpp)
* Purpose : change enum into string

## jsoncpp

* Source : https://github.com/open-source-parsers/jsoncpp
* Version : v1.9.5
* Location in project : [here](../lib/jsoncpp)
* Import Method : https://github.com/open-source-parsers/jsoncpp/wiki/Amalgamated-(Possibly-outdated)
* Purpose : To serialize and deserialize JSON object (e.g., the JSON files of animation and particle system)

## DG2014

* The game library provided from school
* Version : v3.6
* Location in project : [here](../lib/DG2014)
* Purpose : The implementation of images rendering (Reference : [here](../src/GE/Render/Impl))
* Reason of using the plugin : Originally I wanted to replace the whole library from school to my own library. But the implementation of image rendering is too "low level" for a demo game. The main reason of making my own library is to practise my C++ skills, so I gave up that part and just use the library from school.