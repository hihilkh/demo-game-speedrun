#include "Renderer.h"
#include "GE/Core/GameObject.h"

namespace GE::Render
{
	Event<const Renderer&> Renderer::onRendererStarted;
	Event<const Renderer&> Renderer::onRendererDestroying;

	Renderer::Renderer(GameObject& gameObject, std::int16_t renderPriority, RenderLayer::Bitmask renderLayer) :
		Component(gameObject),
		renderPriority(renderPriority),
		renderLayer(renderLayer)
	{
	}

	void Renderer::Start()
	{
		onRendererStarted.Invoke(*this);
	}

	void Renderer::PreDestroy()
	{
		onRendererDestroying.Invoke(*this);
	}

	void Renderer::OnRender(const Transform2DData& viewportData) const
	{
		if (!GetIsEnable()) {
			return;
		}

		Render(viewportData);
	}
}