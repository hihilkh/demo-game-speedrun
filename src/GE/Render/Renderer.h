#pragma once

#include "GE/Core/Component.h"

namespace GE::Render
{
	class Renderer : public Component
	{
		friend GameObject;

	public:
		Renderer(GameObject& gameObject);
		virtual ~Renderer() = default;

	protected:
		virtual void Render() {}

	private:

#pragma region GameObjectに呼び出される関数

		void OnRender();

#pragma endregion
	};
}