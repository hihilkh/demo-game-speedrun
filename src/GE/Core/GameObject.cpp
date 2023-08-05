#include "GameObject.h"
#include "Component.h"
#include "GE/Render/Renderer.h"
#include "GE/Scene/SceneManager.h"
#include "GE/Scene/Scene.h"
#include "Transform2D.h"
#include "GE/Debug/Log.h"
#include <cassert>

namespace GE
{
	GameObject::GameObject(const std::string& name, Scene& scene, GameObject* parent) :
		name(name),
		belongingScene(scene),
		parent(parent),
		transform(std::make_unique<Transform2D>(*this)),
		isActive(true),
		isAwoken(false)
	{
	}

	GameObject::~GameObject() = default;

	GameObject& GameObject::Create(const std::string& name)
	{
		return Create(SceneManagement::SceneManager::GetActiveScene(), name);
	}

	GameObject& GameObject::Create(Scene& scene, const std::string& name)
	{
		return scene.CreateAndOwnGameObject(name, scene, scene.GetIsLoaded());
	}

	GameObject& GameObject::CreatePersistent(const std::string& name)
	{
		return Create(SceneManagement::SceneManager::GetPersistentScene(), name);
	}

	GameObject& GameObject::CreateWithDelayAwake(const std::string& name)
	{
		return CreateWithDelayAwake(SceneManagement::SceneManager::GetActiveScene(), name);
	}

	GameObject& GameObject::CreateWithDelayAwake(Scene& scene, const std::string& name)
	{
		return scene.CreateAndOwnGameObject(name, scene, false);
	}

	GameObject& GameObject::CreatePersistentWithDelayAwake(const std::string& name)
	{
		return CreateWithDelayAwake(SceneManagement::SceneManager::GetPersistentScene(), name);
	}

	GameObject& GameObject::AddChild(const std::string& childName)
	{
		return CreateAndOwnGameObject(childName, belongingScene, isAwoken);
	}

	GameObject& GameObject::AddChildWithDelayAwake(const std::string& childName)
	{
		return CreateAndOwnGameObject(childName, belongingScene, false);
	}
	
	bool GameObject::IsChildOf(const GameObject& other, bool recursive) const
	{
		if (!parent) {
			return false;
		}

		if (parent == &other) {
			return true;
		}

		if (!recursive) {
			return false;
		}

		return parent->IsChildOf(other, recursive);
	}

	GameObject* GameObject::GetChild(const std::string& name) const
	{
		return GetOwnedGameObject(name);
	}

#pragma region ゲームループ と Destroyable

	void GameObject::AwakeIfSceneLoaded()
	{
		if (belongingScene.GetIsLoaded()) {
			OnAwake();
		}
	}

	void GameObject::OnAwake()
	{
		isAwoken = true;

		components.OnAwake();
		ownedGameObjects.OnAwake();
	}

	void GameObject::OnStart()
	{
		OnStartUnstarted();
	}

	bool GameObject::OnStartUnstarted()
	{
		bool hasUnstarted = components.OnStartUnstarted();
		hasUnstarted |= ownedGameObjects.OnStartUnstarted();

		return hasUnstarted;
	}

	void GameObject::OnUpdate()
	{
		if (!isActive || !IsValid()) {
			return;
		}

		components.OnUpdate();
		ownedGameObjects.OnUpdate();
	}

	void GameObject::OnLateUpdate()
	{
		if (!isActive || !IsValid()) {
			return;
		}

		components.OnLateUpdate();
		ownedGameObjects.OnLateUpdate();
	}

	void GameObject::OnEndOfFrame()
	{
		if (!isActive || !IsValid()) {
			return;
		}

		components.OnEndOfFrame();
		ownedGameObjects.OnEndOfFrame();
	}

	void GameObject::OnPreDestroy()
	{
		Destroyable::OnPreDestroy();

		components.OnPreDestroy();
		ownedGameObjects.OnPreDestroy();
	}

	void GameObject::OnDestroy()
	{
		GameObjectOwner* owner = parent ? static_cast<GameObjectOwner*>(parent) : static_cast<GameObjectOwner*>(&belongingScene);
		owner->RemoveOwnedGameObject(*this);
	}

#pragma endregion

	void GameObject::RemoveComponentImmediate(const Component& component)
	{
		components.Remove(component);
	}

	bool operator==(const GameObject& lhs, const GameObject& rhs)
	{
		return &lhs == &rhs;
	}

	bool operator!=(const GameObject& lhs, const GameObject& rhs)
	{
		return !(lhs == rhs);
	}

#pragma region deprecated
	/*
		bool GameObject::SetParent(GameObject* newParent, bool keepWorldTransform)
	{
		if (newParent == parent) {
			return true;
		}

		if (newParent) {
			if (newParent->belongingScene != belongingScene) {
				DEBUG_LOG_ERROR("GameObject：" << name << "は" << newParent->name << "と違うシーンにいる。SetParentできない。");
				return false;
			}

			if (newParent->IsChildOf(*this, true)) {
				DEBUG_LOG_ERROR("GameObject：" << name << "はもともと" << newParent->name << "のparent(再帰的な意味)である。SetParentできない。");
				return false;
			}
		}

		GameObjectOwner* originalOwner = parent ? static_cast<GameObjectOwner*>(parent) : static_cast<GameObjectOwner*>(&belongingScene);
		GameObjectOwner* newOwner = newParent ? static_cast<GameObjectOwner*>(newParent) : static_cast<GameObjectOwner*>(&belongingScene);
		GameObjectOwner::TransferOwnership(*this, *originalOwner, *newOwner);

		Transform2DData temp;
		if (keepWorldTransform) {
			temp = GetTransform().GetWorldTransformData();
		}

		parent = newParent ? newParent : nullptr;

		if (keepWorldTransform) {
			GetTransform().SetWorldPos(temp.pos);
			GetTransform().SetWorldRot(temp.rot);
		}

		return true;
	}
	*/

#pragma endregion

}