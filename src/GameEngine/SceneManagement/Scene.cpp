#include "Scene.h"
#include "Core/GameObject.h"

namespace GE::SceneManagement
{
	Scene::Scene(const std::string& name) : name(name)
	{
	}

	GameObject& Scene::AddGameObject()
	{
		auto& gameObject = gameObjects.emplace_back(std::make_unique<GameObject>());
		return *gameObject;
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
}