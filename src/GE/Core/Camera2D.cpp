#include "Camera2D.h"
#include "Transform2D.h"
#include "GE/Render/Renderer.h"
#include "GameObject.h"
#include "GE/Utils/HandyFunc/GameEngineRelated.h"
#include "GEConfig.h"

namespace GE
{
	struct PreRenderData
	{
		Transform2DData worldTransformData;
		float viewportOffsetX;
		float viewportOffsetY;
	};

	Event<const Camera2D&> Camera2D::onCreated;
	Event<const Camera2D&> Camera2D::onDestroying;

	Camera2D::Camera2D(GameObject& gameObject) :
		Component(gameObject),
		priority(0),
		cullingMask(Render::RenderLayer::all)
	{
	}

	void Camera2D::Awake()
	{
		onCreated.Invoke(*this);
	}

	void Camera2D::PreDestroy()
	{
		onDestroying.Invoke(*this);
	}

	Transform2DData Camera2D::ConvertToViewport(const Transform2D& target, const PreRenderData& preRenderData) const
	{
		// カメラ空間
		Transform2DData result = target.GetWorldTransformData();
		result.pos -= preRenderData.worldTransformData.pos;

		if (preRenderData.worldTransformData.rot != 0) {
			result.pos.Rotate(-preRenderData.worldTransformData.rot);
			result.rot -= preRenderData.worldTransformData.rot;
		}

		// ビューポート
		result.pos.x = preRenderData.viewportOffsetX + result.pos.x;
		result.pos.y = preRenderData.viewportOffsetY - result.pos.y;

		return result;
	}

	void Camera2D::OnRender(const std::vector<const Render::Renderer*>& sortedRenderers) const
	{
		if (!GetEnable()) {
			return;
		}

		PreRenderData preRenderData;
		preRenderData.worldTransformData = GetTransform().GetWorldTransformData();
		preRenderData.viewportOffsetX = GetGEConfig().screenWidth / 2.0f;
		preRenderData.viewportOffsetY = GetGEConfig().screenHeight / 2.0f;

		for (auto renderer : sortedRenderers) {
			if ((cullingMask & renderer->GetRenderLayer()) == 0) {
				continue;
			}

			if (!renderer->GetEnable()) {
				continue;
			}

			renderer->OnRender(ConvertToViewport(renderer->GetTransform(), preRenderData));
		}
	}
}