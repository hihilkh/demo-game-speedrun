#include "Renderer.h"
#include "GE/Core/GameObject.h"
#include "GE/SceneManagement/Scene.h"

namespace GE::Render
{
	Renderer::Renderer(GameObject& gameObject, int renderPriority, RenderLayer::Bitmask renderLayer) :
		Component(gameObject),
		renderPriority(renderPriority),
		renderLayer(renderLayer)
	{
		SceneManagement::Scene& scene = gameObject.GetBelongingScene();
		scene.RegisterRenderer(*this);
	}

	Renderer::~Renderer()
	{
		SceneManagement::Scene& scene = gameObject.GetBelongingScene();
		scene.UnregisterRenderer(*this);
	}

	void Renderer::OnRender(const Transform2DData& viewportData) const
	{
		if (!GetEnable()) {
			return;
		}

		Render(viewportData);
	}
}