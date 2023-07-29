#pragma once

#include "Module.h"
#include <string>
#include <cstdint>

namespace GE::Particle
{
	class ImageModule : public Module
	{
	public:
		explicit ImageModule();

		void SetImage(const std::string& filePath, int16_t renderPriority);

	protected:
		void ApplyModule(Internal::ParticleComponent& particleComponent) override;

	private:
		std::string filePath;
		int16_t renderPriority;
	};
}