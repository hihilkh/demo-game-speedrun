#include "VelocityModule.h"
#include "GE/Utils/Math.h"
#include "UpdateFunc/VelocityUpdateFunc.h"
#include "GE/Particle/Internal/ParticleComponent.h"
#include <string>

namespace GE::Particle
{
	namespace
	{
		const std::string emitAngleNode = "emit_angle";
		const std::string emitSpeedNode = "emit_speed";
		const std::string accelerationNode = "acceleration";
	}

	VelocityModule::VelocityModule(const GE::Json::Value& json) :
		Module(),
		emitAngleRange(JsonHelper::ConvertToRange(json[emitAngleNode])),
		emitSpeedRange(JsonHelper::ConvertToRange(json[emitSpeedNode])),
		acceleration(JsonHelper::ConvertToVector2(json[accelerationNode]))
	{
	}

	void VelocityModule::ApplyModule(Internal::ParticleComponent& particleComponent) const
	{
		float randomEmitAngle = Math::GetRandom(emitAngleRange.x, emitAngleRange.y);
		float randomEmitSpeed = Math::GetRandom(emitSpeedRange.x, emitSpeedRange.y);

		Vector2 initialVelocity(randomEmitSpeed, 0.0f);
		initialVelocity.Rotate(randomEmitAngle);

		particleComponent.AddUpdateFunc(Internal::VelocityUpdateFunc(*this, initialVelocity));
	}
}

