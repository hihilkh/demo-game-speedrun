#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include "GE/Core/GameObject.h"
#include "GE/Core/Internal/GameObjectOwner.h"
#include "GE/Core/Event.h"

namespace GE
{
	class Camera2D;

	namespace Render
	{
		class Renderer;
	}

	namespace SceneManagement
	{
		class SceneManager;
	}

	class Scene : public Internal::GameObjectOwner
	{
		friend class GameEngine;
		friend SceneManagement::SceneManager;

	private:
		enum class State : std::uint8_t
		{
			Initialized,
			Loaded,
			Destroying,
		};

	public:
		static Event<const Scene&> onLoaded;

	public:
		explicit Scene(const std::string& name);
		~Scene();
		Scene(const Scene&) = delete;
		void operator=(const Scene&) = delete;

		const std::string& GetName() const { return name; }
		GameObject* FindGameObject(const std::string& name) const;

		bool GetIsLoaded() const { return state == State::Loaded; }

	private:
		State state;
		const std::string name;
		std::vector<const Camera2D*> cameras;
		std::vector<const Render::Renderer*> renderers;

	private:

#pragma region GameEngineに呼び出される関数

		void OnStartUnstarted();
		void OnUpdate();
		void OnLateUpdate();
		void OnEndOfFrame();

		static void OnRender(const std::vector<Scene*>& scenes);

#pragma endregion

#pragma region SceneManagerに呼び出される関数

		void Load();

#pragma endregion

#pragma region Event Listener

		void RegisterCamera(const Camera2D& camera);
		void UnregisterCamera(const Camera2D& camera);

		void RegisterRenderer(const Render::Renderer& renderer);
		void UnregisterRenderer(const Render::Renderer& renderer);

#pragma endregion
	};

	bool operator==(const Scene& lhs, const Scene& rhs);
	bool operator!=(const Scene& lhs, const Scene& rhs);
}