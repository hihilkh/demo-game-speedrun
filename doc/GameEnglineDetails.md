# ゲームエンジンについて

## 基本資料

* このゲームエンジンは粗末な2Dゲームエンジンです
* 主にUnityの仕組みを参考にしてから作りました
* 言語：`C++`
* ソースコード：[こちら](../src/GE)
* 命名空間：`GE`(名前を長すぎないように、一部の名前をエイリアス付けました(参考：[こちら](../src/GE/Utils/TypeDef.h)))

## 仕組み

* `GameObject`：ゲームの構成の基本単位である。([ソースコード](../src/GE/Core/GameObject.h))
* `Component`：`GameObject`に付けて、機能を追加する部品である。([ソースコード](../src/GE/Core/Component.h))
* `Scene`：`GameObject`を格納して管理するものである。`Scene`の遷移する際、古い`Scene`の`GameObject`を全て破棄します。([ソースコード](../src/GE/Scene)、参考：[こちら](../src/Scene))
* `Transform2D`：`GameObject`の位置と回転を表示する`Component`である。`GameObject`は必ず一つの`Transform2D`を持っています。([ソースコード](../src/GE/Core/Transform2D.h))
* `Image`：2D画像を描画する`Component`である。([ソースコード](../src/GE/Render/Image.h))
* `Camera2D`：`Image`を映って、ゲーム画面で正しく描画する`Component`である。([ソースコード](../src/GE/Core/Camera2D.h))
* `Prefab`：複数の`GameObject`と`Component`を揃って、一つの物とみなして生成できるプリセットである。([ソースコード](../src/GE/Core/Prefab.h)、参考：[こちら](../src/Prefab))
* `GameObject`の親子関係：`GameObject`を他の`GameObject`の`Child`になることができます。([ソースコード](../src/GE/Core/GameObject.h))
* インプットシステム：プレイヤーの入力を取得するシステムである。今、キーボードの入力だけ支援します。([ソースコード](../src/GE/Input))
* `Collider`：当たり判定機能を持っている`Component`である。([ソースコード](../src/GE/Collision/Collider.h))
* 当たり判定システム：`Collider`同士の当たり判定を行うシステムである。([ソースコード](../src/GE/Collision))
* アニメーションシステム：`Image`の描画を時間に沿って変化させるシステムである。([ソースコード](../src/GE/Animation)、参考：[こちら](../src/Prefab/Character/Player/PlayerPrefab.cpp))
* パーティクルシステム：色々なパーティクルモージュルによってパーティクルを表現するシステムである。([ソースコード](../src/GE/Particle)、参考：[こちら](../src/Prefab/Map/Tile/WeakWallTilePrefab.cpp))


### ゲームループ

ゲームを進行している時、毎フレームで下記のようなゲームループを行います。([ソースコード](../src/GE/Core/GameEngine.cpp))

* `TimeUpdatePhase`：ゲーム内の時間を更新します。
* `InputUpdatePhase`：キャッシュしたプレイヤーの入力を整理してから、`InputSystem`を更新します。
* `StartPhase`：新しい生成した`Component`たちの`Start()`関数を呼び出します。
* `UpdatePhase`：`Component`たちの`Update()`関数を呼び出します。その後、`Component`たちの`LateUpdate()`関数を呼び出します。
* `CollisionPhase`：当たり判定を行ってから、該当する`Collider`の位置調整をし、`onCollided`と`onTriggered`の`GE::Event`をトリガーします。
* `AnimationUpdatePhase`：後ろの`RenderPhase`のために、アニメーションの詳細を更新します。
* `RenderPhase`：ゲーム画面で描画します(`Renderer`たちの`Render()`関数を呼び出します)。
* `EndOfFramePhase`：`Component`たちの`EndOfFrame()`関数を呼び出します。主にダングリングポインタを防ぐために使います(参考：[こちら](../src/GE/Animation/Animator.cpp))。
* `DestroyPhase`：破棄を要請された`GameObject`と`Component`を破棄します。破棄する直前、`PreDestroy()`関数を呼び出します。
* `ChangeScenePhase`：`Scene`の遷移を要請した場合、`Scene`を遷移します。

## 開発していた時に使った技術

このゲームエンジンを作る原因は、C++技術を磨きたかったということです。そういうわけで、開発する時に、なるべく外部のプラグインを使わず、自分のコードでエンジンの機能を実装したいと思いました。

下記は、このゲームエンジンを開発していた時に使った技術です。

* STLコンテナ
* STLアルゴリズム
* スマートポインタ
* 右辺値参照
* テンプレート(例：[Vector2](../src/GE/DataType/Vector2.h))
	* 明示的インスタンス化(例：[Vector2](../src/GE/DataType/Vector2.cpp))
	* type_traitsとconcepts(例：[GEConcept](../src/GE/Utils/GEConcept.h))
	* 完全転送(Perfect Forwarding)(例：[GameObject::AddComponent](../src/GE/Core/GameObject.h))
* Pimplイディオム(例：[Collision::Detection::RectDetector](../src/GE/Collision/Detection/RectDetector.h))
* 関数について
	* ラムダ式
	* 関数オブジェクト(例：[Particle::Internal::VelocityUpdateFunc](../src/GE/Particle/Module/UpdateFunc/VelocityUpdateFunc.h))
	* Observerパターン(例：[Event](../src/GE/Core/Event.h))
* Adapterパターン(例：[EnumUtils](../src/GE/Utils/EnumUtils.h))
* Visitorパターン(例：[Collision::Detection::Detector::CheckCollision](../src/GE/Collision/Detection/Detector.h))
* マクロ(例：[Debug::Logging](../src/GE/Debug/Log.h))
* プリプロセッサ(例：[RenderSystemの実装](../src/GE/Render/Impl/DG2014RenderSystem.cpp))
* Precompiled Header(例：[GEHeader](../src/GE/GEHeader.h))

ちょっと本題から離れるけれども、下記は、ゲームエンジンではなく、本編のゲームを開発していた時に使った技術です。

* Factoryパターン(例：[MapFactory](../src/Map/MapFactory.h))
* Stateパターン(例：[PlayerStateMachine](../src/Character/Player/State/PlayerStateMachine.h))

### プラグイン

なるべく外部のプラグインを使わないつもりだったものの、とうとういくつかのプラグインを使いました。

[ここ](./PluginDependency.md)は使っているプラグインの一覧です。

## 不足

* [ログした問題点と改良点](https://github.com/hihilkh/demo-game-speedrun/labels/game%20engine)
* サウンドシステムがありません
* スレッドセーフではないです
* メンバ関数をゲームエンジン内部だけ使えるために、`private`宣言 + `friend`クラスという形はたくさんしました。とうとうゲームエンジン内部のコードは混乱になりました。`public`宣言を使った方がいいかもしれません。
* Unity Editorのようなツールがないので、`Scene`と`Prefab`の構成は自分でC++コードで構築しなければなりません。不便の他に、構築している時、不正な操作(特にゲームループに対して)を防ぐことができません。
* `GameObject`と`Component`の有効性(`GameObject::isActive`、`Component::isEnable`)の機能の実装は不十分だと思います。
* 当たり判定システムは粗末すぎます。色々なバグがあります。
* 当たり判定システムは回転なし`RectCollider`同士の当たり判定だけ支援しています。
* アニメーションシステムは`Image`の描画だけ制御できます。汎用性が低いです。
* パーティクルシステムの細かい実装は`Component`を使います。これは良くないと思います(パフォーマンスの問題もあるし、外部はGetComponent()でパーティクルシステムに影響を与えることもできます)。
* 単体テストと統合テストを用意しなかったので、時々本編のゲームの開発している時、ゲームエンジンのバグを発見して、修正しなければならないこともあります。(特にC++テンプレートに関するコードとGameObjectの親子関係のような複雑の仕組みなど)