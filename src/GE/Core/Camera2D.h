#pragma once

#include <vector>
#include <cstdint>
#include "Component.h"
#include "GE/Render/RenderLayer.h"
#include "Event.h"

// 備考：
// Camera2Dは普通のCameraの簡易版である。
// Camera2Dは常にトップビューで映る。そして、この映る範囲は全ゲーム画面と固定する。
namespace GE
{
	class Transform2D;
	struct Transform2DData;
	class Scene;

	namespace Render
	{
		class Renderer;
	}

	class Camera2D : public Component
	{
		friend class Scene;

	public:
		static Event<const Camera2D&> onStarted;
		static Event<const Camera2D&> onDestroying;

	public:
		Camera2D(GameObject& gameObject);
		~Camera2D() = default;

		int16_t GetPriority() const { return priority; }
		void SetPriority(int16_t priority) { this->priority = priority; }

		Render::RenderLayer::Bitmask GetCullingMask() const { return cullingMask; }
		void SetCullingMask(Render::RenderLayer::Bitmask cullingMask) { this->cullingMask = cullingMask; }

	protected:
		void Start() override;
		void PreDestroy() override;

	private:
		/// <summary>
		/// <para>大きければ大きいほど画面の上に描画する。負数も許す。</para>
		/// GE::Renderer::RendererのrenderPriorityと違う。
		/// </summary>
		int16_t priority;
		Render::RenderLayer::Bitmask cullingMask;

	private:

#pragma region Sceneに呼び出される関数

		/// <summary>
		/// 描画の処理。有効にする時のみ
		/// </summary>
		 void OnRender(const std::vector<const Render::Renderer*>& sortedRenderers) const;

#pragma endregion

		 Transform2DData ConvertToViewport(const Transform2D& target, const struct PreRenderData& preRenderData) const;
	};
}