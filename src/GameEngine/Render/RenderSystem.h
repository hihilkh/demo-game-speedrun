#pragma once

namespace GE
{
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
	public:
		static void Init(const RenderSystemInitParams& params, const GEConfig& config);

		static void StartRender();
		static void FinishRender();
	};
}