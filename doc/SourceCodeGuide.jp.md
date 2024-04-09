[![en](https://img.shields.io/badge/lang-en-red.svg)](./SourceCodeGuide.md)
[![jp](https://img.shields.io/badge/lang-jp-green.svg)](./SourceCodeGuide.jp.md)

# ソースコードのご案内

## ブランチ

* `master`：主なブランチです。
* `feature/speedrun`：学校の一年後期の進級制作の開発のブランチ。このブランチで、学校が提供したライブラリを使っています。
* `feature/reconstruct`と`feature/ge_enhancement_<日付け>`：`feature/speedrun`をもとに、学校のライブラリから自作のゲームライブラリに置き換えたり、コードを最適化したり、色々なことを改造します。
* `profiling`ディレクトリのブランチ：改造前後のパフォーマンスをプロファイリングしてから、比較と分析します。

## フォルダ構成

```
./
├ data/					// ゲーム内使ったデータ
├ doc/					// 書類
├ imageSrc/				// 自分で作った画像の編集できるファイル
├ lib/					// サードパーティーのプラグイン
├ src/					// 自分で作ったコード
    ├ GE/				// 自作ゲームライブラリ
    ├ WinMain.cpp			// プログラムのエントリーポイント
    └ ...
├ GPG_2020.sln				// VisualStudioのソリューション
└ ...
```

### `src`フォルダをもっと説明

* `TitleScene`、`GameScene`、`EndingScene`フォルダ：シーンに関連するコード
* `PrepareScene`：このゲームの最初のシーンです。ゲーム全体に必要なことを用意したら、すぐに`TitleScene`に遷移します。
* `Character/Player`フォルダ：プレイヤーに関連するコード
	* `State`フォルダ：プレイヤーの動作をStateパターンで制御します。
* `Map`フォルダ：ゲームシーンのマップの生成に関連するコード
	* `MapObject`：マップの中に入るオブジェクト
	* `Tile`：マップを構成するタイル
* `Prefab`フォルダ：Prefabを構築するコードです。Unityの`Prefab`またはUnrealの`Blueprint`のような役割です。
* `Scene/Builder`フォルダ：シーンを構築するコードです。Unityの`Scene`またはUnrealの`Level`のような役割です。

## その他

* [コードスタンダード](./CodeStandard.jp.md)
* [自作ゲームライブラリ](./GameLibraryDetails.jp.md)
* [使ったプラグイン](./PluginDependency.jp.md)
* [外部素材](./ExternalResources.jp.md)