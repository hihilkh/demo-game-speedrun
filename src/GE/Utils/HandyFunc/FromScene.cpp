#include "FromScene.h"
#include "GE/Scene/SceneManager.h"
#include "GE/Scene/Scene.h"

namespace GE
{
	GameObject* FindGameObject(const std::string& name)
	{
		return Scene::SceneManager::GetActiveScene().FindGameObject(name);
	}
}