#include "EmissionModule.h"
#include "GE/Core/GameObject.h"
#include "GE/Utils/Math.h"
#include "GE/Core/Transform2D.h"
#include "GE/Particle/Internal/ParticleComponent.h"
#include <string>

namespace GE::Particle
{
	namespace
	{
		const std::string rotNode = "rot";
	}

	EmissionModule::EmissionModule(const GE::Json::Value& json) :
		Module(),
		rotRange(JsonHelper::ConvertToRange(json[rotNode]))
	{
	}

	void EmissionModule::ApplyModule(Internal::ParticleComponent& particleComponent) const
	{
		float randomRot = Math::GetRandom(rotRange.x, rotRange.y);
		particleComponent.gameObject.GetTransform().SetRot(randomRot);
	}
}

