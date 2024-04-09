[![en](https://img.shields.io/badge/lang-en-red.svg)](./SourceCodeGuide.md)
[![jp](https://img.shields.io/badge/lang-jp-green.svg)](./SourceCodeGuide.jp.md)

# More About Source Code

## Branches

This project is originally an assignment when I was studying in Japan.

* `master` : The main branch.
* `feature/speedrun` : The develop branch for the original game as a school assignment. The game library from school is used in this branch.
* `feature/reconstruct` and `feature/ge_enhancement_<date>` : The branches of reconstructing the original game in `feature/speedrun` branch and replace the game library from school by my own game library. Also, some other changes has been done, e.g., optimization.
* Branches in `profiling` directory : Profile the performance before and after the reconstruction and do comparison and analysis.

## Folder Structure

```
./
├ data/					// The data used in the game
├ doc/					// Documentation
├ imageSrc/				// The raw image files I have made
├ lib/					// Third-party plugins
├ src/					// The codes written by me
    ├ GE/				// My game library
    ├ WinMain.cpp			// The entry point of the program
    └ ...
├ GPG_2020.sln				// The VisualStudio solution file
└ ...
```

### More About `src` Folder

* `TitleScene`, `GameScene` and `EndingScene` folders : The codes of different scenes of the game
* `PrepareScene` : The first scene of the game. After all the necessary config is set up, , it will move to `TitleScene`.
* `Character/Player` folder : The codes about player character.
	* `State` folder : Use state pattern to control player's action.
* `Map` folder : The codes about map generation in game scene.
	* `MapObject` : Map objects are objects that are placed into a map.
	* `Tile` : Tiles make up a map.
* `Prefab` folder : The codes that construct prefabs. It works like `Prefab` in Unity or `Blueprint` in Unreal.
* `Scene/Builder` folder : The codes that construct scenes. It works like `Scene` in Unity or `Level` in Unreal.

## Other References

* [Code Standard](./CodeStandard.md)
* [More About Game Library](./GameLibraryDetails.md)
* [Used Plugins](./PluginDependency.md)
* [External Resources](./ExternalResources.md)