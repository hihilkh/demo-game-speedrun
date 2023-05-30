﻿#pragma once

#include "Component.h"
#include "GE/Render/RenderLayer.h"
#include <vector>

// 備考：
// Camera2Dは普通のCameraの簡易版である。
// Camera2Dは常にトップビューで映る。そして、この映る範囲は全ゲーム画面と固定する。
namespace GE
{
	class Transform2D;
	struct Transform2DData;

	namespace Render
	{
		class Renderer;
	}

	namespace Scene
	{
		class Scene;
	}

	class Camera2D : public Component
	{
		friend class Scene::Scene;

	public:
		Camera2D(GameObject& gameObject);
		~Camera2D() = default;

		int GetPriority() const { return priority; }
		void SetPriority(int priority) { this->priority = priority; }

		Render::RenderLayer::Bitmask GetCullingMask() const { return cullingMask; }
		void SetCullingMask(Render::RenderLayer::Bitmask cullingMask) { this->cullingMask = cullingMask; }

	protected:
		void Awake() override;
		void PreDestroy() override;

	private:
		/// <summary>
		/// <para>大きければ大きいほど画面の上に描画する。負数も許す。</para>
		/// GE::Renderer::RendererのrenderPriorityと違う。
		/// </summary>
		int priority;
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