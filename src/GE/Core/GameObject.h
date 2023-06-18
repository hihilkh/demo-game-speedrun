﻿#pragma once

#include "Internal/GameObjectOwner.h"
#include <vector>
#include <memory>
#include <functional>
#include <type_traits>
#include <string>
#include "Internal/Destroyable.h"
#include "PrefabDeclaration.h"

namespace GE
{
	class Component;
	class Transform2D;
	class Scene;

	namespace Render
	{
		class Renderer;
	}

	class GameObject : public Internal::GameObjectOwner, public Internal::Destroyable
	{
		friend Internal::GameLoopObjectContainer<GameObject>;
		friend Component;

	public:
		GameObject(const std::string& name, Scene& scene, GameObject* parent);
		~GameObject();	// Componentとかが前方宣言できるために、デストラクタを宣言し、cppで定義する

		GameObject(const GameObject&) = delete;
		void operator=(const GameObject&) = delete;

		const std::string& GetName() const { return name; }
		void SetName(const std::string& newName) { name = newName; }

		bool GetActive() const { return isActive; }
		void SetActive(bool isActive) { this->isActive = isActive; }

		Scene& GetBelongingScene() const { return belongingScene; }

		/// <summary>
		/// ActiveSceneで新しいGameObjectを生成する
		/// </summary>
		static GameObject& Create(const std::string& name = "GameObject");

		/// <summary>
		/// 指定のsceneで新しいGameObjectを生成する
		/// </summary>
		static GameObject& Create(Scene& scene, const std::string& name = "GameObject");

		/// <summary>
		/// PersistentSceneで新しいGameObjectを生成する。つまり、sceneを遷移する際にも破棄されない。
		/// </summary>
		static GameObject& CreatePersistent(const std::string& name = "GameObject");

		/// <summary>
		/// 新しいGameObjectを生成し、childになる
		/// </summary>
		GameObject& AddChild(const std::string& childName);

		GameObject* Parent() const { return parent; }	// 自分がconstになってもparentを変更されることができます
		bool SetParent(GameObject* newParent, bool keepWorldTransform = false);
		bool IsChildOf(const GameObject& other, bool recursive) const;
		GameObject* GetChild(const std::string& name) const;

		const Transform2D& GetTransform() const { return *transform; }
		Transform2D& GetTransform() { return *transform; }

		template<typename T, typename... Args> T& AddComponent(Args&&... args);
		template<typename T> T* GetComponent() const;
		template<typename T> T* GetComponentInChildren() const;
		template<typename T> T* GetComponentInParent() const;
		template<typename T> std::vector<T*> GetComponents() const;
		template<typename T> std::vector<T*> GetComponentsInChildren() const;
		template<typename T> std::vector<T*> GetComponentsInParent() const;

		// TODO : RemoveComponent()

	private:
		template<typename T> void GetComponents(std::vector<T*>& outContainer) const;
		template<typename T> void GetComponentsInChildren(std::vector<T*>& outContainer) const;
		template<typename T> void GetComponentsInParent(std::vector<T*>& outContainer) const;

	private:
		std::string name;
		Scene& belongingScene;
		GameObject* parent;		// parentが破棄される前に、このインスタンスのchildrenを全て破棄するので、parentはダングリングポインタになるはずがない
		const std::unique_ptr<Transform2D> transform;
		Internal::GameLoopObjectContainer<Component> components;

		bool isActive;
		bool isAwoken;

	private:

#pragma region ゲームループ

		void AwakeIfSceneLoaded();

		void OnAwake();
		void OnStart();
		bool OnStartUnstarted();
		void OnUpdate();
		void OnLateUpdate();
		void OnEndOfFrame();

#pragma endregion

#pragma region Destroyable

		void OnPreDestroy() override;
		void OnDestroy() override;

#pragma endregion

#pragma region Prefabに呼び出される関数

		template<typename PrefabT>
		friend PrefabReturnType<PrefabT> Instantiate(PrefabT prefab);

		template<typename PrefabT>
		friend PrefabReturnType<PrefabT> Instantiate(PrefabT prefab, Scene& scene);

		template<typename PrefabT>
		friend PrefabReturnType<PrefabT> InstantiatePersistent(PrefabT prefab);

		static GameObject& CreateWithDelayAwake(const std::string& name = "GameObject");
		static GameObject& CreateWithDelayAwake(Scene& scene, const std::string& name = "GameObject");
		static GameObject& CreatePersistentWithDelayAwake(const std::string& name = "GameObject");

#pragma endregion

		void RemoveComponentImmediate(const Component& component);

	};

	bool operator==(const GameObject& lhs, const GameObject& rhs);
	bool operator!=(const GameObject& lhs, const GameObject& rhs);

#pragma region 関数テンプレート定義

	template<typename T, typename... Args>
	T& GameObject::AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of_v<Component, T>, "The type must be a component");

		Component& component = components.Add<T>(isAwoken, *this, std::forward<Args>(args)...);
		T& componentInT = static_cast<T&>(component);

		return componentInT;
	}

	template<typename T>
	T* GameObject::GetComponent() const
	{
		static_assert(std::is_base_of_v<Component, T>, "The type must be a component");

		for (auto it = components.SimpleBegin(), itEnd = components.SimpleEnd(); it != itEnd; ++it) {
			T* castValue = dynamic_cast<T*>((*it).get());
			if (castValue) {
				return castValue;
			}
		}

		return nullptr;
	}

	template<typename T>
	T* GameObject::GetComponentInChildren() const
	{
		T* result = GetComponent<T>();
		if (result) {
			return result;
		}

		for (auto it = ownedGameObjects.SimpleBegin(), itEnd = ownedGameObjects.SimpleEnd(); it != itEnd; ++it) {
			result = (*it)->GetComponentInChildren<T>();
			if (result) {
				return result;
			}
		}

		return nullptr;
	}

	template<typename T>
	T* GameObject::GetComponentInParent() const
	{
		T* result = GetComponent<T>();
		if (result) {
			return result;
		}

		if (parent) {
			return parent->GetComponentInParent();
		} else {
			return nullptr;
		}
	}

	template<typename T>
	std::vector<T*> GameObject::GetComponents() const
	{
		std::vector<T*> result;
		GetComponents(result);
		return result;
	}

	template<typename T>
	std::vector<T*> GameObject::GetComponentsInChildren() const
	{
		std::vector<T*> result;
		GetComponentsInChildren(result);
		return result;
	}

	template<typename T>
	std::vector<T*> GameObject::GetComponentsInParent() const
	{
		std::vector<T*> result;
		GetComponentsInParent(result);
		return result;
	}

	template<typename T>
	void GameObject::GetComponents(std::vector<T*>& outContainer) const
	{
		static_assert(std::is_base_of_v<Component, T>, "The type must be a component");

		for (auto it = components.SimpleBegin(), itEnd = components.SimpleEnd(); it != itEnd; ++it) {
			T* castValue = dynamic_cast<T*>((*it).get());
			if (castValue) {
				outContainer.push_back(castValue);
			}
		}
	}

	template<typename T>
	void GameObject::GetComponentsInChildren(std::vector<T*>& outContainer) const
	{
		GetComponents(outContainer);

		for (auto it = ownedGameObjects.SimpleBegin(), itEnd = ownedGameObjects.SimpleEnd(); it != itEnd; ++it) {
			(*it)->GetComponentsInChildren<T>(outContainer);
		}
	}

	template<typename T>
	void GameObject::GetComponentsInParent(std::vector<T*>& outContainer) const
	{
		GetComponents(outContainer);
		if (parent) {
			parent->GetComponentsInParent(outContainer);
		}
	}

#pragma endregion
}