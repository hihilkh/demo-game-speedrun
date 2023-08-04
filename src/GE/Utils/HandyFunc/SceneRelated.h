#pragma once

#include <string>

namespace GE
{
	class GameObject;

	/// <summary>
	/// 全てのLoaded SceneでGameObjectを探す
	/// </summary>
	GameObject* FindGameObject(const std::string& name);

	void LoadScene(const std::string& sceneName);
}