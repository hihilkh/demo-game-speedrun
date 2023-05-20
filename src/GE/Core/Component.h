#pragma once

namespace GE
{
	class GameObject;
	class Transform2D;

	class Component
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
		void SetEnable(bool isEnable) { this->isEnable = isEnable; }

		const Transform2D& Transform() const;
		Transform2D& Transform();

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
		bool isEnable;

	private:

#pragma region GameObjectに呼び出される関数

		void OnAwake();
		void OnStart();
		void OnUpdate();
		void OnLateUpdate();

#pragma endregion

	};
}