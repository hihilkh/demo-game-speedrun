#pragma once

#include "Module.h"
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Vector2.h"
#include "JsonHelper.h"

namespace GE::Particle
{
	class VelocityModule : public Module
	{
	public:
		explicit VelocityModule(const GE::Json::Value& json);

		const Vector2& GetAcceleration() const { return acceleration; }

	protected:
		void ApplyModule(Internal::ParticleComponent& particleComponent) const override;

	private:
		Vector2 emitAngleRange;
		Vector2 emitSpeedRange;
		Vector2 acceleration;
	};
}