#pragma once

#include <cstdint>
#include "GE/Core/Component.h"
#include "RenderLayer.h"
#include "GE/Core/Event.h"

namespace GE
{
	class Camera2D;
	struct Transform2DData;
}

namespace GE::Render
{
	class Renderer : public Component
	{
		friend Camera2D;

	public:
		static Event<const Renderer&> onRendererStarted;
		static Event<const Renderer&> onRendererDestroying;

	public:
		Renderer(GameObject& gameObject, std::int16_t renderPriority, RenderLayer::Bitmask renderLayer);
		virtual ~Renderer() = default;

		std::int16_t GetRenderPriority() const { return renderPriority; }
		void SetRenderPriority(std::int16_t renderPriority) { this->renderPriority = renderPriority; }

		RenderLayer::Bitmask GetRenderLayer() const { return renderLayer; }
		void SetRenderLayer(RenderLayer::Bitmask renderLayer) { this->renderLayer = renderLayer; }

	protected:
		virtual void Render(const Transform2DData& viewportData) const {}

		void Start() override;
		void PreDestroy() override;

	private:
		/// <summary>
		/// 大きければ大きいほど画面の上に描画する。負数も許す。
		/// </summary>
		std::int16_t renderPriority;
		RenderLayer::Bitmask renderLayer;

	private:

#pragma region Camera2Dに呼び出される関数

		void OnRender(const Transform2DData& viewportData) const;

#pragma endregion
	};
}