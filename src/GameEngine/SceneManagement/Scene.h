﻿#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Core/GameObject.h"

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
		std::string name;
		std::vector<std::unique_ptr<GameObject>> gameObjects;

	private:
		void Update();
		void LateUpdate();
		void Render();
	};
}