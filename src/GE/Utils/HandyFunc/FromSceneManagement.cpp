#include "FromSceneManagement.h"
#include "GE/SceneManagement/SceneManager.h"
#include "GE/SceneManagement/Scene.h"

namespace GE
{
	GameObject* FindGameObject(const std::string& name)
	{
		return SceneManagement::SceneManager::GetActiveScene().FindGameObject(name);
	}
}