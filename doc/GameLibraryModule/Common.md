# 共通のモジュールについて

## Event

* Observerパターンを運用するために、`Event`クラステンプレートを作りました。
* `AddListener()`と`RemoveListener()`関数によって、`Listener`を追加と削除します。
* `Invoke()`関数によって、`Event`を行い、`Listener`たちに通知します。
* `Listener`については、一般的な関数ポインタの他に、`MemberFunc`というラッパークラスも用意して、クラスインスタンスのメンバ関数も`Listener`になることができます。

### 参照

* [`Event`のソースコード](../../src/GE/Core/Event.h)
* [`MemberFunc`のソースコード](../../src/GE/Core/MemberFunc.h)
* [使用例(`onGoalReached` Eventの`Invoke()`)](../../src/Map/MapObject/GoalObject.cpp)
* [使用例(`onGoalReached` Eventの`Listener`)](../../src/GameScene/GameSceneDirector.cpp)

## Coroutine

* コンポーネントの`StartCoroutine()`関数を使って、プレディケート(predicate)を指定し、その条件を`true`になったら、次の処理を続けます。
* Unityの`Coroutine`モジュールと似ています。しかし、今の実装はUnityの`StartCoroutine()`より、`Invoke()`ともっと似ています。
* `Yield`命名空間の中のクラスをプレディケートとして使えます。
	* 現在、`Yield::WaitSecond`だけ実装しました。Unityの`WaitForSeconds`と似ています。

### 参照

* [`Coroutine`のソースコード](../../src/GE/Core/Coroutine.h)
* [`Yield`のソースコード](../../src/GE/Yield)
* [使用例](../../src/TransformUtils/PositionMovement.cpp)