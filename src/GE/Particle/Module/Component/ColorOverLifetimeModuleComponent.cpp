#include "ColorOverLifetimeModuleComponent.h"
#include "../ColorOverLifetimeModule.h"
#include "CoreModuleComponent.h"
#include "GE/Core/GameObject.h"
#include "GE/Render/Image.h"

namespace GE::Particle::Internal
{
	ColorOverLifetimeModuleComponent::ColorOverLifetimeModuleComponent(GameObject& gameObject, const ColorOverLifetimeModule& colorOverLifetimeModule) :
		Component(gameObject),
		colorOverLifetimeModule(colorOverLifetimeModule)
	{
	}

	void ColorOverLifetimeModuleComponent::Update()
	{
		auto coreModuleComponent = gameObject.GetComponent<CoreModuleComponent>();
		auto image = gameObject.GetComponent<Render::Image>();
		if (coreModuleComponent && image) {
			float normalizedLifetime = coreModuleComponent->GetNormalizedLifetime();
			Color currentColor = colorOverLifetimeModule.GetColor(normalizedLifetime);
			image->SetColor(currentColor);
		}
	}
}