#include "Scene.h"
#include "Core/GameObject.h"

namespace GE::SceneManagement
{
	Scene::Scene(const std::string& name) : name(name)
	{
	}

	GameObject& Scene::AddGameObject()
	{
		std::unique_ptr<GameObject>& gameObject = gameObjects.emplace_back();
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