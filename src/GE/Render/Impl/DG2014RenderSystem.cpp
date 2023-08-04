#include "GE/Utils/PreprocessorDef.h"

#if _RENDERER == RENDERER_DG2014

#include "../RenderSystem.h"
#include "../RenderSystemInitParams.h"
#include <memory>
#include <DG2014/DG2014_DGObject.h>
#include "GE/Core/GEConfig.h"
#include "GE/Utils/HandyFunc/GameEngineRelated.h"

namespace GE::Render
{
	namespace
	{
		std::shared_ptr<DG::DGObject> dg;
	}

#pragma region 他のDirectXのモジュールのために用意する
	ID3D10Device* GetDirectXDevice()
	{
		if (dg) {
			return &(dg->Device());
		} else {
			return nullptr;
		}
	}

	void TempEnd2DRender()
	{
		dg->End2D();
	}

	void Resume2DRender()
	{
		dg->Begin2D();
	}

#pragma endregion

	void RenderSystem::Init(const RenderSystemInitParams& params, const GEConfig& config)
	{
		dg = DG::DGObject::Create(
			params.hWnd,
			config.screenWidth,
			config.screenHeight,
			1,
			false,
			config.screenWidth,
			config.screenHeight);
	}

	void RenderSystem::OnStartRender()
	{
		Color bgColor = GE::GetGEConfig().bgColor;
		dg->Begin(ML::Color(bgColor.a, bgColor.r, bgColor.g, bgColor.b));

		dg->EffectState().RS_Def2D();
		dg->EffectState().BS_Alpha();

		dg->Begin2D();
	}

	void RenderSystem::OnFinishRender()
	{
		dg->End2D();
		dg->End();
	}
}

#endif