#include "GameObject.h"
#include "Component.h"
#include "GE/Render/Renderer.h"
#include "GE/SceneManagement/SceneManager.h"
#include "GE/SceneManagement/Scene.h"
#include "Transform2D.h"
#include "GE/Debug/Log.h"
#include <cassert>

namespace GE
{
	GameObject::GameObject(const std::string& name, SceneManagement::Scene& scene, GameObject* parent) :
		name(name),
		belongingScene(scene),
		parent(parent),
		transform(std::make_unique<Transform2D>(*this)),
		isActive(true)
	{
	}

	GameObject::~GameObject() = default;

	GameObject& GameObject::Create(const std::string& name)
	{
		return Create(SceneManagement::SceneManager::GetActiveScene(), name);
	}

	GameObject& GameObject::Create(SceneManagement::Scene& scene, const std::string& name)
	{
		return scene.CreateAndOwnGameObject(name, scene);
	}

	GameObject& GameObject::CreateChild(const std::string& childName)
	{
		return CreateAndOwnGameObject(childName, this->belongingScene);
	}

	bool GameObject::SetParent(GameObject* newParent, bool keepWorldTransform)
	{
		if (newParent == parent) {
			return true;
		}

		if (newParent) {
			if (newParent->belongingScene != belongingScene) {
				DEBUG_LOG_WARNING("GameObject：" << name << "は" << newParent->name << "と違うシーンにいる。SetParentできない。");
				return false;
			}

			if (newParent->IsChildOf(*this, true)) {
				DEBUG_LOG_WARNING("GameObject：" << name << "はもともと" << newParent->name << "のparent(再帰的な意味)である。SetParentできない。");
				return false;
			}
		}

		GameObjectOwner* originalOwner = parent ? static_cast<GameObjectOwner*>(parent) : static_cast<GameObjectOwner*>(&belongingScene);
		std::unique_ptr<GameObject> tempSelf = originalOwner->ReleaseGameObjectOwnership(*this);
		assert(tempSelf && "なぜか自分のunique_ptrが取れない");

		GameObjectOwner* newOwner = newParent ? static_cast<GameObjectOwner*>(newParent) : static_cast<GameObjectOwner*>(&belongingScene);
		newOwner->TakeGameObjectOwnership(std::move(tempSelf));

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

#define EXECUTE_BY_ORDER(func) {\
	for (auto& component : components) {\
		component->func;\
	}\
	for (auto& child : children) {\
		child->func;\
	}\
}

	void GameObject::OnAwake()
	{
		EXECUTE_BY_ORDER(OnAwake());
	}

	void GameObject::OnStart()
	{
		EXECUTE_BY_ORDER(OnStart());
	}

	void GameObject::OnUpdate()
	{
		if (!isActive || !IsValid()) {
			return;
		}

		EXECUTE_BY_ORDER(OnUpdate());
	}

	void GameObject::OnLateUpdate()
	{
		if (!isActive || !IsValid()) {
			return;
		}

		EXECUTE_BY_ORDER(OnLateUpdate());
	}

	void GameObject::OnEndOfFrame()
	{
		if (!isActive || !IsValid()) {
			return;
		}

		EXECUTE_BY_ORDER(OnEndOfFrame());
	}

	void GameObject::OnPreDestroy()
	{
		Destroyable::OnPreDestroy();

		EXECUTE_BY_ORDER(OnPreDestroy());
	}

#undef EXECUTE_BY_ORDER

	void GameObject::OnDestroy()
	{
		GameObjectOwner* owner = parent ? static_cast<GameObjectOwner*>(parent) : static_cast<GameObjectOwner*>(&belongingScene);
		owner->ReleaseGameObjectOwnership(*this);
	}

	bool GameObject::CheckIsInActiveScene()
	{
		return GetBelongingScene() == SceneManagement::SceneManager::GetActiveScene();
	}

#pragma endregion

	bool GameObject::RemoveComponentImmediate(const Component& component)
	{
		auto target = std::find_if(
			components.begin(),
			components.end(),
			[&component](const auto& fromContainer) { return *fromContainer == component; });

		if (target == components.end()) {
			return false;
		} else {
			components.erase(target);
			return true;
		}
	}

	bool operator==(const GameObject& lhs, const GameObject& rhs)
	{
		return &lhs == &rhs;
	}

	bool operator!=(const GameObject& lhs, const GameObject& rhs)
	{
		return !(lhs == rhs);
	}
}