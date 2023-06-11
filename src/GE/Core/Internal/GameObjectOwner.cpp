#include "GameObjectOwner.h"
#include "GE/Core/GameObject.h"
#include "GE/Scene/Scene.h"

namespace GE::Internal
{
	GameObject* GameObjectOwner::GetOwnedGameObject(const std::string& name) const
	{
		// まず最下位のGameObjectから探す
		for (auto& gameObject : GetGameObjectContainer()) {
			if (gameObject->name == name) {
				return gameObject.get();
			}
		}

		for (auto& gameObject : GetGameObjectContainer()) {
			GameObject* result = gameObject->GetOwnedGameObject(name);
			if (result) {
				return result;
			}
		}

		return nullptr;
	}

	GameObject& GameObjectOwner::CreateAndOwnGameObject(const std::string& name, Scene& scene, bool isDelayInit)
	{
		struct UniquePtrEnabler : public GameObject
		{
			UniquePtrEnabler(const std::string& name, Scene& scene, GameObject* parent) :
				GameObject(name, scene, parent) {}
		};

		GameObject* parent = dynamic_cast<GameObject*>(this);
		auto& gameObject = GetGameObjectContainer().emplace_back(std::make_unique<UniquePtrEnabler>(name, scene, parent));
		if (!isDelayInit) {
			gameObject->InitIfSceneLoaded();
		}

		return *gameObject;
	}

	std::unique_ptr<GameObject> GameObjectOwner::ReleaseGameObjectOwnership(GameObject& gameObject)
	{
		auto& container = GetGameObjectContainer();
		auto target = std::find_if(
			container.begin(),
			container.end(),
			[&gameObject](const auto& fromContainer) { return *fromContainer == gameObject; });

		if (target == container.end()) {
			return std::unique_ptr<GameObject>();
		} else {
			std::unique_ptr<GameObject> returnValue = std::move(*target);
			container.erase(target);
			return returnValue;
		}
	}

	void GameObjectOwner::TakeGameObjectOwnership(std::unique_ptr<GameObject>&& gameObject)
	{
		GetGameObjectContainer().emplace_back(std::move(gameObject));
	}
}