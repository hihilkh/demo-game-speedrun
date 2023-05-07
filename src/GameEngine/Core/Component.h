#pragma once

#include "GameLoopBase.h"

namespace GE
{
	class GameObject;

	class Component : public Internal::GameLoopBase
	{
		// TODO : Temp
		// isActive (global base)

	public:
		// GameObjectが無効になる前に、必ず持っているComponentを破棄する
		GameObject& gameObject;

	public:
		Component() = delete;
		Component(const Component&) = delete;
		void operator=(const Component&) = delete;

		/// <summary>
		/// 全てのComponentの派生クラスは第一仮引数がGameObject&であるコンストラクタを持っている必要がある
		/// </summary>
		Component(GameObject& gameObject);
		virtual ~Component() = default;

	protected:
		/// <summary>
		/// 生成した後の最初の処理。有効無効にかかわらず呼び出される
		/// </summary>
		virtual void Awake() {}
		/// <summary>
		/// Awake()段階の次の処理。有効無効にかかわらず呼び出される
		/// </summary>
		virtual void Start() {}
		/// <summary>
		/// 毎フレームの処理。有効にする時のみ
		/// </summary>
		virtual void Update() {}
		/// <summary>
		/// Update段階の次の処理。有効にする時のみ
		/// </summary>
		virtual void LateUpdate() {}

	private:
		void OnAwake() override;
		void OnStart() override;
		void OnUpdate() override;
		void OnLateUpdate() override;
	};
}