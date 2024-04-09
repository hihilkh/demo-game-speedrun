[![en](https://img.shields.io/badge/lang-en-red.svg)](./Common.md)
[![jp](https://img.shields.io/badge/lang-jp-green.svg)](./Common.jp.md)

# About Common Modules

## Event

* In order to use observer pattern, I have made the `Event` class template.
* A `Listener` can be added or removed by `AddListener()` and `RemoveListener()` methods.
* Use `Invoke()` method to trigger the `Event` and notify all the `Listeners`.
* You can set a function pointer to be a `Listener`. You can use the `MemberFunc` wrapper class to wrap a member function of a class instance and set it to be a `Listener`.

### References

* [Source Code of `Event`](../../src/GE/Core/Event.h)
* [Source Code of `MemberFunc`](../../src/GE/Core/MemberFunc.h)
* [Example (`Invoke()` method of `onGoalReached` Event)](../../src/Map/MapObject/GoalObject.cpp)
* [Example (`Listener` of `onGoalReached` Event)](../../src/GameScene/GameSceneDirector.cpp)

## Coroutine

* You can start a `Coroutine` by `StartCoroutine()` method of a Component. A predicate and a function need to be passed into `StartCoroutine()`. When the condition of the predicate becomes `true`, it will trigger the function.
* It is similar to the `Coroutine` module in Unity. However, it is closer to the `Invoke()` method than the `StartCoroutine()` method in Unity.
* Some predefined predicates can be used in `Yield` namespace.
	* Currently, only `Yield::WaitSecond` is implemented. It is similar to `WaitForSeconds` in Unity.

### References

* [Source Code of `Coroutine`](../../src/GE/Core/Coroutine.h)
* [Source Code of `Yield`](../../src/GE/Yield)
* [Example](../../src/TransformUtils/PositionMovement.cpp)