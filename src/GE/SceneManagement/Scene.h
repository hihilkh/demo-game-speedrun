#pragma once

#include <string>
#include <vector>
#include <memory>
#include "GE/Core/GameObject.h"
#include "GE/Core/GameObjectOwner.h"

namespace GE::SceneManagement
{
	class Scene : public Internal::GameObjectOwner
	{
		friend class GameEngine;

	public:
		explicit Scene(const std::string& name);
		Scene(const Scene&) = delete;
		void operator=(const Scene&) = delete;

		const std::string& GetName() const { return name; }

	private:
		const std::string name;
		std::vector<std::unique_ptr<GameObject>> gameObjects;

	private:
		void OnUpdate();
		void OnLateUpdate();
		void OnRender();

#pragma region GameObjectOwner

		std::vector<std::unique_ptr<GameObject>>& GetGameObjectContainer() override { return gameObjects; }

#pragma endregion
	};

	bool operator==(const Scene& lhs, const Scene& rhs);
	bool operator!=(const Scene& lhs, const Scene& rhs);
}