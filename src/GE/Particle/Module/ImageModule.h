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

		void ApplyModule(GameObject& baseObject) override;

		void SetImage(const std::string& filePath, int16_t renderPriority);

	private:
		std::string filePath;
		int16_t renderPriority;
	};
}