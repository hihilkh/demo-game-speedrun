#pragma once

namespace GE::Render::Internal
{
	class RenderBase
	{
	public:
		virtual ~RenderBase() = default;

		virtual void OnRender() {}
	};
}