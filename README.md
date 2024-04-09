[![en](https://img.shields.io/badge/lang-en-red.svg)](./README.md)
[![jp](https://img.shields.io/badge/lang-jp-green.svg)](./README.jp.md)

---

**Remark** :

This project is done when I was studying in Japan. Some contents are written in Japanese, e.g., comments in the codes, git commit messages, GitHub's issues, etc.

---

# To Begin With

It is a simple 2D game project made with C++. The game itselt is quite simple, but I also made a simple 2D game library.

This project is originally an assignment when I was studying in Japan. Before going to Japan to study, I mainly used Unity and C# in my previous company. When I was doing this assignment, I felt that developing with C++ was not as smooth as that with with C#. Also, the game library provided by school was not that easy to use. So I wanted to make my own game library from scratch to practice my c++ skill.

For more details of the source code, please refer to [here](./doc/SourceCodeGuide.md).

For more details of the game library I made, please refer to [here](./doc/GameLibraryDetails.md).

# Demo Video

https://github.com/hihilkh/demo-game-speedrun/assets/35343910/409cc33f-c4d2-4509-9568-51cb1408d62a

# Introduction

* Title : Speedrun
* Gameplay : Control the character, make use of the terrain, break the walls that block your way and reach the goal as fast as you can.

# About the Development

* Development Period :
	* 2022/12 ~ 2023/02 : Develop the game with the game library from school
	* 2023/04 ~ 2023/08 : Write my own game library to replace school’s library
* Language : C++20
* IDE : Visual Studio 2022
* Graphic API : DirectX 12
* More About Source Code : [here](./doc/SourceCodeGuide.md)
* More About My Game Library : [here](./doc/GameLibraryDetails.md)

# About the Release

* [Download Executable File](https://github.com/hihilkh/demo-game-speedrun/releases/latest)
* Platform : Windows 64bit

# Game Control

* Please use keyboard for the control.

| Key         | Game Scene   | UI          |
| ----------- | ----------- | ----------- |
| Arrow Keys     | Character movement 　　     | Menu selection |
| X       　　| Hold : Running   | Confirm button 　　　　　|

# What I Have Learned

* The game itself is too simple and the game library is also quite rough and bugs remains (especially about the collision detection). But I think it is a great achievement to make a game library by my own and without much help from third-party plugins.
* When I was making the game library, I studied quite a lot about memory management, the efficiency of the codes, template, relation between linker and compiler, etc. I also learned some common techniques, syntax and best practices of C++. I became more familiar with C++ development. ([Used Techniques](./doc/GameLibraryDetails.md#used-techniques))
* I have tried to use some design patterns in this project and had more understanding about the principle of those patterns. ([Used Techniques](./doc/GameLibraryDetails.md#used-techniques))
* As I was replacing the school’s library with mine, I have done some profiling and optimization to the game library to ensure the game performance was kept. I have also tried to write more flexible codes so that it is easier for further changes.
