#pragma once

#include "Module.h"
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Vector2.h"

namespace GE::Particle
{
	class EmissionModule : public Module
	{
	public:
		explicit EmissionModule();

		void ApplyModule(GameObject& baseObject) override;

		void SetRotationRange(float fromDegree, float toDegree) { this->rotRange = Vector2(fromDegree, toDegree);  }
		void SetRotationRange(float constantDegree) { SetRotationRange(constantDegree, constantDegree); }

	private:
		Vector2 rotRange;
	};
}