#include "GE/Utils/PreprocessorDef.h"

#if _RENDERER == RENDERER_DG2014

#include "../RenderSystem.h"
#include "../RenderSystemInitParams.h"
#include <memory>
#include "DG2014/DG2014_DGObject.h"
#include "GE/Core/GEConfig.h"

namespace GE::Render
{
	namespace
	{
		std::shared_ptr<DG::DGObject> dg;
	}

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

	void RenderSystem::StartRender()
	{
		// TODO : カメラによっての背景色
		dg->Begin(dg->EffectState().param.bgColor);

		dg->EffectState().RS_Def2D();
		dg->EffectState().BS_Alpha();

		dg->Begin2D();
	}

	void RenderSystem::FinishRender()
	{
		dg->End2D();
		dg->End();
	}
}

#endif