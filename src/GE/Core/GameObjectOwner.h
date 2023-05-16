#pragma once

#include <vector>
#include <memory>
#include <string>

namespace GE
{
	class GameObject;

	namespace SceneManagement
	{
		class Scene;
	}
}

namespace GE::Internal
{
	class GameObjectOwner
	{
		friend GameObject;

	public:
		virtual ~GameObjectOwner() = default;

	private:
		virtual std::vector<std::unique_ptr<GameObject>>& GetGameObjectContainer() = 0;

	private:
		GameObject& CreateAndOwnGameObject(const std::string& name, SceneManagement::Scene& scene);
		std::unique_ptr<GameObject> ReleaseGameObjectOwnership(GameObject& gameObject);
		void TakeGameObjectOwnership(std::unique_ptr<GameObject>&& gameObject);


	};
}