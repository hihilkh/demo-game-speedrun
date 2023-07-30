#pragma once

#include "EmissionModule.h"
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Rect.h"
#include "JsonHelper.h"

namespace GE::Particle
{
	class RectEmissionModule : public EmissionModule
	{
	public:
		explicit RectEmissionModule(const GE::Json::Value& json);

	protected:
		void ApplyModule(Internal::ParticleComponent& particleComponent) const override;

	private:
		Rect rect;
	};
}