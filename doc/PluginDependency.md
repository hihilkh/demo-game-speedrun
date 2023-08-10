# 使っているプラグイン

## magic_enum

* ソース：https://github.com/Neargye/magic_enum
* バージョン：v0.9.0
* プロジェクトの中の位置：[こちら](../lib/magic_enum.hpp)
* 使い道：enumをstringに変換するために使います

## jsoncpp

* ソース：https://github.com/open-source-parsers/jsoncpp
* バージョン：v1.9.5
* プロジェクトの中の位置：[こちら](../lib/jsoncpp)
* 導入方法：https://github.com/open-source-parsers/jsoncpp/wiki/Amalgamated-(Possibly-outdated)
* 使い道：jsonのシリアライズとデシリアライズするために使います(例：AnimationとParticleSystemのjsonファイル)

## DG2014

* 学校が提供したライブラリ
* バージョン：v3.6
* プロジェクトの中の位置：[こちら](../lib/DG2014)
* 使い道：画像の描画の実装(参考：[こちら](../src/GE/Render/Impl))
* 使う原因：最初は学校が提供したライブラリを全て自分で書くコードで置き換えるつもりでした。でも、ゲームエンジンを自分で作る原因は、C++技術を磨くということなので、ゲームエンジンを100%自分で作るのをあまりこだわりません。画像の描画の実装は複雑だと思います。また、デモ版ゲーム作りにとって、画像の描画の実装は「Low Level」すぎると思います。そういうわけで、この部分は学校が提供したライブラリで実装しました。