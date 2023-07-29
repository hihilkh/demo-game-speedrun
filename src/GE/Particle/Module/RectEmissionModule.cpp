#include "RectEmissionModule.h"
#include "GE/Core/GameObject.h"
#include "GE/Utils/Math.h"
#include "GE/Core/Transform2D.h"

namespace GE::Particle
{
	RectEmissionModule::RectEmissionModule() :
		EmissionModule(),
		rect()
	{
	}

	void RectEmissionModule::ApplyModule(GameObject& baseObject)
	{
		EmissionModule::ApplyModule(baseObject);

		float randomX = Math::GetRandom(rect.x, rect.OppositeX());
		float randomY = Math::GetRandom(rect.y, rect.OppositeY());

		baseObject.GetTransform().SetPos(randomX, randomY);
	}
}

