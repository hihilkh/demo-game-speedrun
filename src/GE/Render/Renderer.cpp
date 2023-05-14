#include "Renderer.h"

namespace GE::Render
{
	Renderer::Renderer(GameObject& gameObject) : Component(gameObject)
	{
	}

	void Renderer::OnRender()
	{
		if (!GetEnable()) {
			return;
		}

		Render();
	}
}