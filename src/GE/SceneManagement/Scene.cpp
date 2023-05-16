#include "Scene.h"
#include "GE/Core/GameObject.h"

namespace GE::SceneManagement
{
	Scene::Scene(const std::string& name) : name(name)
	{
	}

	void Scene::OnUpdate()
	{
		for (auto& gameObject : gameObjects) {
			gameObject->OnUpdate();
		}
	}

	void Scene::OnLateUpdate()
	{
		for (auto& gameObject : gameObjects) {
			gameObject->OnLateUpdate();
		}
	}

	void Scene::OnRender()
	{
		for (auto& gameObject : gameObjects) {
			gameObject->OnRender();
		}
	}

	bool operator==(const Scene& lhs, const Scene& rhs)
	{
		return &lhs == &rhs;
	}

	bool operator!=(const Scene& lhs, const Scene& rhs)
	{
		return !(lhs == rhs);
	}
}