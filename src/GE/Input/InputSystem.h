#pragma once

#include "Key.h"

namespace GE
{
	class GameEngine;
}

// 今特定なキーボードのキーだけ支援している。
// マウスとかゲームパッドとかアナログ入力とか支援していない。
namespace GE::Input
{
	// 備考：
	// KeyDown, KeyUp, KeyOnについて：
	// 1フレームごとにKeyDown、KeyUp、KeyOnの状態を更新する
	// KeyDown：キーを押す瞬間、KeyDownがtrueになる。1フレーム後falseに戻す
	// KeyUp：キーを離す瞬間、KeyUpがtrueになる。1フレーム後falseに戻す
	// KeyOn：キーを押しているとき、KeyOnがtrueになる（キーを押す瞬間も）
	// 特殊状況：
	// 1フレームの中でOnKeyDownもOnKeyUpもしていた：
	// その場合になったら、KeyDownとKeyUpを同時にtrueになる。さらに、KeyOnはfalseになる。

	/// <summary>
	/// このフレームでkeyCodeをKeyDownをしたことあるか
	/// </summary>
	bool GetKeyDown(KeyCode keyCode);
	/// <summary>
	/// このフレームでkeyCodeをKeyUpをしたことあるか
	/// </summary>
	bool GetKeyUp(KeyCode keyCode);
	/// <summary>
	/// このフレームでkeyCodeはonであるか
	/// </summary>
	bool GetKeyOn(KeyCode keyCode);

	// TODO
	//void RegisterKeyDown(KeyCode keyCode, std::function<void()> action);
	//void UnregisterKeyDown(KeyCode keyCode, std::function<void()> action);
	//void RegisterKeyUp(KeyCode keyCode, std::function<void()> action);
	//void UnregisterKeyUp(KeyCode keyCode, std::function<void()> action);
	//void RegisterKeyOn(KeyCode keyCode, std::function<void()> action);
	//void UnregisterKeyOn(KeyCode keyCode, std::function<void()> action);]

	class InputSystem
	{
		friend GameEngine;

	private:
		static void OnUpdate();
	};

	/// <summary>
	/// MainProgramに呼び出される関数
	/// </summary>
	namespace Internal
	{
		void OnKeyDown(KeyCode keyCode);
		void OnKeyUp(KeyCode keyCode);
	}
}