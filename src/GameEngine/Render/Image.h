#pragma once

#include "Renderer.h"

namespace GE::Render
{
	class Image : public Renderer
	{
	public:
		Image(GameObject& gameObject);

	protected:
		void Render() override;
	};
}