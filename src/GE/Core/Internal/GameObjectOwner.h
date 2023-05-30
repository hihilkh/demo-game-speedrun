#pragma once

#include <vector>
#include <memory>
#include <string>

namespace GE
{
	class GameObject;

	namespace Scene
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

	protected:
		GameObject* GetOwnedGameObject(const std::string& name) const;

	private:
		virtual std::vector<std::unique_ptr<GameObject>>& GetGameObjectContainer() = 0;
		virtual const std::vector<std::unique_ptr<GameObject>>& GetGameObjectContainer() const = 0;

	private:
		GameObject& CreateAndOwnGameObject(const std::string& name, Scene::Scene& scene);
		std::unique_ptr<GameObject> ReleaseGameObjectOwnership(GameObject& gameObject);
		void TakeGameObjectOwnership(std::unique_ptr<GameObject>&& gameObject);
	};
}