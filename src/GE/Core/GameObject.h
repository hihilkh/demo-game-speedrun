#pragma once

#include "GameObjectOwner.h"
#include <vector>
#include <memory>
#include <functional>
#include <type_traits>
#include <string>

namespace GE
{
	class Component;
	class Transform2D;

	namespace Render
	{
		class Renderer;
	}
	namespace SceneManagement
	{
		class Scene;
	}

	class GameObject : public Internal::GameObjectOwner
	{
		friend SceneManagement::Scene;
		friend Internal::GameObjectOwner;

	public:
		~GameObject();	// Componentとかが前方宣言できるために、デストラクタを宣言し、cppで定義する

		GameObject(const GameObject&) = delete;
		void operator=(const GameObject&) = delete;

		const std::string& GetName() const { return name; }
		void SetName(const std::string& newName) { name = newName; }

		bool GetActive() const { return isActive; }
		void SetActive(bool isActive) { this->isActive = isActive; }

		SceneManagement::Scene& GetBelongingScene() const { return belongingScene; }

		/// <summary>
		/// ActiveSceneで新しいGameObjectを生成する
		/// </summary>
		static GameObject& Create(const std::string& name);

		/// <summary>
		/// 指定のsceneで新しいGameObjectを生成する
		/// </summary>
		static GameObject& Create(const std::string& name, SceneManagement::Scene& scene);

		/// <summary>
		/// 新しいGameObjectを生成し、childになる
		/// </summary>
		GameObject& CreateChild(const std::string& childName);

		GameObject* Parent() const { return parent; }	// 自分がconstになってもparentを変更されることができます
		bool SetParent(GameObject* newParent);
		bool IsChildOf(const GameObject& other, bool recursive) const;

		const Transform2D& Transform() const { return *transform; }
		Transform2D& Transform() { return *transform; }

		template<typename T>
		T& AddComponent(auto&&... args);
		// TODO : Temp
		// GetEnable (global base)
		// Destroy
		// GetChild
		// GetComponent

	private:
		std::string name;
		SceneManagement::Scene& belongingScene;
		GameObject* parent;		// parentが破棄される前に、このインスタンスのchildrenを全て破棄するので、parentはダングリングポインタになるはずがない
		const std::unique_ptr<Transform2D> transform;
		std::vector<std::unique_ptr<Component>> nonRenderComponents;
		std::vector<std::unique_ptr<Render::Renderer>> renderers;
		std::vector<std::unique_ptr<GameObject>> children;
		bool isActive;

	private:
		GameObject(const std::string& name, SceneManagement::Scene& scene, GameObject* parent);

#pragma region ゲームループ

		/// <summary>
		/// 生成した後の最初の処理。有効無効にかかわらず呼び出される
		/// </summary>
		void OnAwake();
		/// <summary>
		/// Awake()段階の次の処理。有効無効にかかわらず呼び出される
		/// </summary>
		void OnStart();
		/// <summary>
		/// 毎フレームの処理。有効にする時のみ
		/// </summary>
		void OnUpdate();
		/// <summary>
		/// Update段階の次の処理。有効にする時のみ
		/// </summary>
		void OnLateUpdate();

#pragma endregion

#pragma region GameObjectOwner

		std::vector<std::unique_ptr<GameObject>>& GetGameObjectContainer() override { return children; }

#pragma endregion

	};

#pragma region 関数テンプレート定義

	template<typename T>
	inline T& GameObject::AddComponent(auto&&... args)
	{
		static_assert(std::is_base_of_v<Component, T>, "The type must be a component");

		auto add = [&]() -> T& {
			if constexpr (std::is_base_of_v<Render::Renderer, T>) {
				auto& component = renderers.emplace_back(std::make_unique<T>(*this, args...));
				return static_cast<T&>(*component);
			} else {
				auto& component = nonRenderComponents.emplace_back(std::make_unique<T>(*this, args...));
				return static_cast<T&>(*component);
			}
		};

		T& component = add();
		component.OnAwake();
		component.OnStart();

		return component;
	}

#pragma endregion

	bool operator==(const GameObject& lhs, const GameObject& rhs);
	bool operator!=(const GameObject& lhs, const GameObject& rhs);
}