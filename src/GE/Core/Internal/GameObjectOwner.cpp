#include "GameObjectOwner.h"
#include "GE/Core/GameObject.h"

namespace GE::Internal
{
	GameObject* GameObjectOwner::GetOwnedGameObject(const std::string& name) const
	{
		// まず最下位のGameObjectから探す
		for (auto it = ownedGameObjects.SimpleBegin(), itEnd = ownedGameObjects.SimpleEnd(); it != itEnd; ++it) {
			if ((*it)->GetName() == name) {
				return (*it).get();
			}
		}

		for (auto it = ownedGameObjects.SimpleBegin(), itEnd = ownedGameObjects.SimpleEnd(); it != itEnd; ++it) {
			GameObject* result = (*it)->GetOwnedGameObject(name);
			if (result) {
				return result;
			}
		}

		return nullptr;
	}

	GameObject& GameObjectOwner::CreateAndOwnGameObject(const std::string& name, Scene& scene, bool isAwakeImmediate)
	{
		GameObject* parent = dynamic_cast<GameObject*>(this);
		return ownedGameObjects.Add(isAwakeImmediate, name, scene, parent);
	}

	void GameObjectOwner::TransferOwnership(const GameObject& gameObject, GameObjectOwner& from, GameObjectOwner& to)
	{
		GameLoopObjectContainer<GameObject>::Transfer(gameObject, from.ownedGameObjects, to.ownedGameObjects);
	}

	void GameObjectOwner::RemoveOwnedGameObject(GameObject& gameObject)
	{
		ownedGameObjects.Remove(gameObject);
	}
}