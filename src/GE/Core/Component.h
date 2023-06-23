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
	namespace Internal
	{
		template<typename T>
		class GameLoopObjectContainer;
	}

	class Component : public Internal::Destroyable
	{
		friend Internal::GameLoopObjectContainer<Component>;

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
		// TODO : 
		// 現在SceneまたはPrefabの生成段階の中、このゲームループの概念を違反することもある。
		// 例１：
		// - あるComponentはInit()関数がある。
		// - そして、Prefabを生成している時(までPrefab全体が生成しなかった)、このComponentのInit()を呼び出す。
		// - この場合、Init()はAwake()の前に呼び出されるようになる。
		// 例２：
		// - あるPrefabの生成段階の中、あるGameObjectを生成する。
		// - この時、GameObjectはAwake()が呼び出されない(Prefabはまだ全体が生成していない)。
		// - そして、GameObject::SetParent()によってこのGameObjectを他のすでにAwake()したGameObjectのchildになる。
		// - この場合、このGameObjectと従っているComponentsはAwake()が呼び出されない。
		// - (追記：今、GameObject::SetParent()はdeprecatedになった)

		/// <summary>
		/// <para>生成した後の最初の処理。有効無効にかかわらず、下記の場合に一回だけ呼び出される</para>
		/// <para>- (Prefabではない、読み込んだ(Loaded) Sceneの中で)生成した直後</para>
		/// <para>- (Prefabである、読み込んだSceneの中で)Prefab全体が生成した直後</para> 
		/// <para>- (まだ読み込まないSceneの中で)Sceneを読み込む時</para> 
		/// <para>こういうわけで、Awake()が呼び出される時、すべてのGameObjectとComponentはすでに生成したことが保証する</para> 
		/// </summary>
		virtual void Awake() {}
		/// <summary>
		/// <para>Awake()段階の次の処理。有効無効にかかわらず、読み込んだ(Loaded) SceneのStartPhaseに一回だけ呼び出される</para>
		/// <para>- もしあるComponentのStart()の中で新しいComponentを生成すれば、この新しいComponentも同じフレームでStart()が呼び出される</para>
		/// <para>- もしあるComponentのUpdate()の中で新しいComponentを生成すれば、この新しいComponentは次のフレームでStart()が呼び出される。つまり、現在のフレームのゲームループを行わないと言える</para> 
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
		/// <summary>
		/// 破棄直前の処理
		/// </summary>
		virtual void PreDestroy() override {}

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

#pragma endregion

	};

	bool operator==(const Component& lhs, const Component& rhs);
	bool operator!=(const Component& lhs, const Component& rhs);
}