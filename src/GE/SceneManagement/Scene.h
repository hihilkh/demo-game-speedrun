#pragma once

#include <string>
#include <vector>
#include <memory>
#include "GE/Core/GameObject.h"
#include "GE/Core/GameObjectOwner.h"

namespace GE
{
	class Camera2D;

	namespace Render
	{
		class Renderer;
	}
}

namespace GE::SceneManagement
{
	class Scene : public Internal::GameObjectOwner
	{
		friend class GameEngine;
		friend class Camera2D;
		friend class Render::Renderer;

	public:
		explicit Scene(const std::string& name);
		~Scene();
		Scene(const Scene&) = delete;
		void operator=(const Scene&) = delete;

		const std::string& GetName() const { return name; }

	private:
		bool isDestructing;
		const std::string name;
		std::vector<std::unique_ptr<GameObject>> gameObjects;
		std::vector<const Camera2D*> cameras;
		std::vector<const Render::Renderer*> renderers;

	private:
		void OnUpdate();
		void OnLateUpdate();
		void OnRender();

#pragma region Camera2DとRendererに呼び出される関数

		void RegisterCamera(const Camera2D& camera);
		void UnregisterCamera(const Camera2D& camera);

		void RegisterRenderer(const Render::Renderer& renderer);
		void UnregisterRenderer(const Render::Renderer& renderer);

#pragma endregion

#pragma region GameObjectOwner

		std::vector<std::unique_ptr<GameObject>>& GetGameObjectContainer() override { return gameObjects; }

#pragma endregion
	};

	bool operator==(const Scene& lhs, const Scene& rhs);
	bool operator!=(const Scene& lhs, const Scene& rhs);
}