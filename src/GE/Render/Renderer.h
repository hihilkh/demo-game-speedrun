#pragma once

#include "GE/Core/Component.h"
#include "RenderBase.h"

namespace GE::Render
{
	class Renderer : public Component, public Internal::RenderBase
	{
	public:
		Renderer(GameObject& gameObject);
		virtual ~Renderer() = default;

	protected:
		virtual void Render() {}

	private:
		void OnRender() override;
	};
}