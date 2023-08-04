#pragma once

#include <functional>
#include "GE/Render/RenderSystemInitParams.h"

namespace GE
{
	struct GEConfig;
	struct MainProgramInitParams;
	namespace Render
	{
		struct RenderSystemInitParams;
	}

	class MainProgram
	{
	public:
		struct OtherInitParamsSet
		{
			Render::RenderSystemInitParams renderSystemInitParams;
		};

		static OtherInitParamsSet Prepare(const MainProgramInitParams& params, const GEConfig& config);

		static int Start(std::function<void()> gameLoop);
	};

}