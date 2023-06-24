#include "Renderer.h"
#include "GE/Core/GameObject.h"

namespace GE::Render
{
	Event<const Renderer&> Renderer::onStarted;
	Event<const Renderer&> Renderer::onDestroying;

	Renderer::Renderer(GameObject& gameObject, int16_t renderPriority, RenderLayer::Bitmask renderLayer) :
		Component(gameObject),
		renderPriority(renderPriority),
		renderLayer(renderLayer)
	{
	}

	void Renderer::Start()
	{
		onStarted.Invoke(*this);
	}

	void Renderer::PreDestroy()
	{
		onDestroying.Invoke(*this);
	}

	void Renderer::OnRender(const Transform2DData& viewportData) const
	{
		if (!GetIsEnable()) {
			return;
		}

		Render(viewportData);
	}
}