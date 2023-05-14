#pragma once

#include <functional>

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
		static Render::RenderSystemInitParams Prepare(const MainProgramInitParams& params, const GEConfig& config);
		static int Start(std::function<void()> gameLoop);
	};

}