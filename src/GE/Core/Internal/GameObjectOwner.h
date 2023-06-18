#pragma once

#include <vector>
#include <memory>
#include <string>
#include "GameLoopObjectContainer.h"

namespace GE
{
	class GameObject;
	class Scene;
}

namespace GE::Internal
{
	class GameObjectOwner
	{
		friend GameObject;

	public:
		virtual ~GameObjectOwner() = default;

	protected:
		GameLoopObjectContainer<GameObject> ownedGameObjects;

	protected:
		GameObject* GetOwnedGameObject(const std::string& name) const;
		static void TransferOwnership(const GameObject& gameObject, GameObjectOwner& from, GameObjectOwner& to);

	private:

#pragma region GameObjectに呼び出される関数

		GameObject& CreateAndOwnGameObject(const std::string& name, Scene& scene, bool isAwakeImmediate);
		void RemoveOwnedGameObject(GameObject& gameObject);

#pragma endregion
	};
}