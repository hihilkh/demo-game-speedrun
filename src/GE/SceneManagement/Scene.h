#pragma once

#include <string>
#include <vector>
#include <memory>
#include "GE/Core/GameObject.h"

namespace GE::SceneManagement
{
	class Scene
	{
		friend class GameEngine;

	public:
		explicit Scene(const std::string& name);
		Scene(const Scene&) = delete;
		void operator=(const Scene&) = delete;

		const std::string& GetName() const { return name; }
		GameObject& AddGameObject();

	private:
		const std::string name;
		std::vector<std::unique_ptr<GameObject>> gameObjects;

	private:
		void OnUpdate();
		void OnLateUpdate();
		void OnRender();
	};
}