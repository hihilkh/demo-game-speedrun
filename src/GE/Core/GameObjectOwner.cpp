#include "GameObjectOwner.h"
#include "GameObject.h"
#include "GE/SceneManagement/Scene.h"

namespace GE::Internal
{
	GameObject& GameObjectOwner::CreateAndOwnGameObject(const std::string& name, SceneManagement::Scene& scene)
	{
		struct UniquePtrEnabler : public GameObject
		{
			UniquePtrEnabler(const std::string& name, SceneManagement::Scene& scene, GameObject* parent) :
				GameObject(name, scene, parent) {}
		};

		GameObject* parent = dynamic_cast<GameObject*>(this);
		auto& gameObject = GetGameObjectContainer().emplace_back(std::make_unique<UniquePtrEnabler>(name, scene, parent));
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