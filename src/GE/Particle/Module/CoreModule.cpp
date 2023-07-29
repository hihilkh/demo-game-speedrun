#include "CoreModule.h"
#include "GE/Core/GameObject.h"
#include "Component/CoreModuleComponent.h"

namespace GE::Particle
{
	CoreModule::CoreModule() :
		life(0.0f)
	{
	}

	void CoreModule::ApplyModule(GameObject& baseObject)
	{
		baseObject.AddComponent<Internal::CoreModuleComponent>(*this);
	}
}

