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

	void Scene::Update()
	{
		for (auto& gameObject : gameObjects) {
			gameObject->Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (auto& gameObject : gameObjects) {
			gameObject->LateUpdate();
		}
	}

	void Scene::Render()
	{
		for (auto& gameObject : gameObjects) {
			gameObject->Render();
		}
	}
}