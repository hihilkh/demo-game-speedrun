#include "ImageModule.h"
#include "GE/Debug/Log.h"
#include "GE/Core/GameObject.h"
#include "GE/Render/Image.h"
#include "GE/Particle/Internal/ParticleComponent.h"

namespace GE::Particle
{
	ImageModule::ImageModule() :
		Module(),
		filePath(""),
		renderPriority()
	{
	}

	void ImageModule::SetImage(const std::string& filePath, int16_t renderPriority)
	{
		this->filePath = filePath;
		this->renderPriority = renderPriority;
	}

	void ImageModule::ApplyModule(Internal::ParticleComponent& particleComponent)
	{
		if (filePath == "") {
			DEBUG_LOG_WARNING("filePathは空になる。ParticleにImageが追加できない。");
			return;
		}

		auto& image = particleComponent.gameObject.AddComponent<Render::Image>(filePath);
		image.SetRenderPriority(renderPriority);
	}
}

