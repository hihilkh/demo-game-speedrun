#include "GEHeader.h"
#include "GameObject.h"
#include "Component.h"
#include "Renderer.h"

namespace GE
{
	GameObject::~GameObject() = default;

	void GameObject::Awake()
	{
		ExecuteByOrder(
			[](auto& object) { object.Awake(); }
		);
	}

	void GameObject::Start()
	{
		ExecuteByOrder(
			[](auto& object) { object.Start(); }
		);
	}

	void GameObject::Update()
	{
		if (!GetEnable()) {
			return;
		}

		ExecuteByOrder(
			[](auto& object) { object.Update(); }
		);
	}

	void GameObject::LateUpdate()
	{
		if (!GetEnable()) {
			return;
		}

		ExecuteByOrder(
			[](auto& object) { object.LateUpdate(); }
		);
	}

	void GameObject::Render()
	{
		if (!GetEnable()) {
			return;
		}

		for (auto& renderer : renderers) {
			renderer->Render();
		}

		for (auto& child : children) {
			child->Render();
		}
	}

	void GameObject::ExecuteByOrder(void (*func)(Internal::GameLoopObject&))
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
}