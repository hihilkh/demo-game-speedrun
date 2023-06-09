#include "FromScene.h"
#include "GE/Scene/SceneManager.h"
#include "GE/Scene/Scene.h"

namespace GE
{
	GameObject* FindGameObject(const std::string& name)
	{
		std::vector<Scene::Scene*> loadedScenes = Scene::SceneManager::GetLoadedScenes();
		GameObject* result = nullptr;

		for (const auto scene : loadedScenes) {
			result = scene->FindGameObject(name);

			if (result) {
				return result;
			}
		}

		return result;
	}
}