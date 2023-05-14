#include "GameObject.h"
#include "Component.h"
#include "GE/Render/Renderer.h"
#include "GE/SceneManagement/SceneManager.h"
#include "GE/SceneManagement/Scene.h"

namespace GE
{
	GameObject::GameObject() = default;
	GameObject::~GameObject() = default;

	GameObject& GameObject::CreateEmpty()
	{
		return SceneManagement::SceneManager::GetActiveScene().AddGameObject();
	}

#pragma region ゲームループ

	void GameObject::OnAwake()
	{
		ExecuteByOrder(
			[](auto& object) { object.OnAwake(); }
		);
	}

	void GameObject::OnStart()
	{
		ExecuteByOrder(
			[](auto& object) { object.OnStart(); }
		);
	}

	void GameObject::OnUpdate()
	{
		if (!GetEnable()) {
			return;
		}

		ExecuteByOrder(
			[](auto& object) { object.OnUpdate(); }
		);
	}

	void GameObject::OnLateUpdate()
	{
		if (!GetEnable()) {
			return;
		}

		ExecuteByOrder(
			[](auto& object) { object.OnLateUpdate(); }
		);
	}

	void GameObject::OnRender()
	{
		if (!GetEnable()) {
			return;
		}

		ExecuteRenderByOrder(
			[](auto& object) { object.OnRender(); }
		);
	}

	void GameObject::ExecuteByOrder(void (*func)(Internal::GameLoopBase&))
	{
		for (auto& component : nonRenderComponents) {
			func(*component);
		}

		for (auto& renderer : renderers) {
			func(*renderer);
		}

		for (auto& child : children) {
			func(*child);
		}
	}

	void GameObject::ExecuteRenderByOrder(void (*func)(Render::Internal::RenderBase&))
	{
		for (auto& renderer : renderers) {
			func(*renderer);
		}

		for (auto& child : children) {
			func(*child);
		}
	}

#pragma endregion

}