#include "EmissionModule.h"
#include "GE/Core/GameObject.h"
#include "GE/Utils/Math.h"
#include "GE/Core/Transform2D.h"

namespace GE::Particle
{
	EmissionModule::EmissionModule() :
		Module(),
		rotRange()
	{
	}

	void EmissionModule::ApplyModule(GameObject& baseObject)
	{
		float randomRot = Math::GetRandom(rotRange.x, rotRange.y);
		baseObject.GetTransform().SetRot(randomRot);
	}
}

