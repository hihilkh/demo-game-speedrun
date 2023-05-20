#pragma once

#include "GE/Core/Component.h"
#include "RenderLayer.h"

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
		Renderer(GameObject& gameObject, int renderPriority, RenderLayer::Bitmask renderLayer);
		virtual ~Renderer();

		int GetRenderPriority() const { return renderPriority; }
		void SetRenderPriority(int renderPriority) { this->renderPriority = renderPriority; }

		RenderLayer::Bitmask GetRenderLayer() const { return renderLayer; }
		void SetRenderLayer(RenderLayer::Bitmask renderLayer) { this->renderLayer = renderLayer; }

	protected:
		virtual void Render(const Transform2DData& viewportData) const {}

	private:
		/// <summary>
		/// 大きければ大きいほど画面の上に描画する。負数も許す。
		/// </summary>
		int renderPriority;
		RenderLayer::Bitmask renderLayer;

	private:

#pragma region Camera2Dに呼び出される関数

		void OnRender(const Transform2DData& viewportData) const;

#pragma endregion
	};
}