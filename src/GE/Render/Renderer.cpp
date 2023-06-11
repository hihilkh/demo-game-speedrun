#include "Renderer.h"
#include "GE/Core/GameObject.h"

namespace GE::Render
{
	Event<const Renderer&> Renderer::onCreated;
	Event<const Renderer&> Renderer::onDestroying;

	Renderer::Renderer(GameObject& gameObject, int renderPriority, RenderLayer::Bitmask renderLayer) :
		Component(gameObject),
		renderPriority(renderPriority),
		renderLayer(renderLayer)
	{
	}

	void Renderer::Awake()
	{
		onCreated.Invoke(*this);
	}

	void Renderer::PreDestroy()
	{
		onDestroying.Invoke(*this);
	}

	void Renderer::OnRender(const Transform2DData& viewportData) const
	{
		if (!GetEnable()) {
			return;
		}

		Render(viewportData);
	}
}