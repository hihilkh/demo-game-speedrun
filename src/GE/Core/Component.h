#pragma once

#include "Internal/Destroyable.h"
#include <memory>
#include <vector>
#include <functional>

namespace GE
{
	class GameObject;
	class Transform2D;
	class Coroutine;

	class Component : public Internal::Destroyable
	{
		friend class GameObject;

	public:
		// GameObjectが無効になる前に、必ず持っているComponentを破棄するので、GameObjectの参照を持つ
		GameObject& gameObject;

	public:
		Component(const Component&) = delete;
		void operator=(const Component&) = delete;

		/// <summary>
		/// 全てのComponentの派生クラスは第一仮引数がGameObject&であるコンストラクタを持っている必要がある
		/// </summary>
		explicit Component(GameObject& gameObject);
		virtual ~Component() = default;

		bool GetEnable() const { return isEnable; }
		virtual void SetEnable(bool isEnable) { this->isEnable = isEnable; }

		const Transform2D& GetTransform() const;
		Transform2D& GetTransform();

	protected:

		std::weak_ptr<Coroutine> StartCoroutine(const std::function<bool()>& predicate, const std::function<void()>& func);
		void StopCoroutine(std::weak_ptr<Coroutine> coroutine);
		void StopAllCoroutines();

#pragma region ゲームループ

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
		/// <summary>
		/// ほぼフレームの最後の段階(Destroy段階の直前)。ダングリングポインタの防止ための処理とか。有効にする時のみ
		/// </summary>
		virtual void EndOfFrame() {}

#pragma endregion

	private:
		bool isEnable;
		std::vector<std::shared_ptr<Coroutine>> coroutines;

	private:

#pragma region GameObjectに呼び出される関数

		void OnAwake();
		void OnStart();
		void OnUpdate();
		void OnLateUpdate();
		void OnEndOfFrame();

#pragma endregion

		void UpdateCoroutines();

#pragma region Destroyable

		void OnDestroy() override;
		bool CheckIsInActiveScene() override;

#pragma endregion

	};

	bool operator==(const Component& lhs, const Component& rhs);
	bool operator!=(const Component& lhs, const Component& rhs);
}