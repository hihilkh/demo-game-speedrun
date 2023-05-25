#pragma once

namespace GE
{
	class GameEngine;
	struct GEConfig;

	namespace Render
	{
		struct RenderSystemInitParams;
	}
}

namespace GE::Render
{
	class RenderSystem
	{
		friend GameEngine;
	private:
		static void Init(const RenderSystemInitParams& params, const GEConfig& config);

		static void StartRender();
		static void FinishRender();
	};
}