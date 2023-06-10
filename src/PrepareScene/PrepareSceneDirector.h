#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"

namespace PrepareScene
{
	class Director : public Component
	{
	public:
		explicit Director(GameObject& gameObject);

	protected:
		void Start() override;
	};
}