#pragma once

#include "Module.h"
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Vector2.h"
#include "JsonHelper.h"

namespace GE::Particle
{
	class EmissionModule : public Module
	{
	public:
		explicit EmissionModule(const GE::Json::Value& json);

	protected:
		void ApplyModule(Internal::ParticleComponent& particleComponent) const override;

	private:
		Vector2 rotRange;
	};
}