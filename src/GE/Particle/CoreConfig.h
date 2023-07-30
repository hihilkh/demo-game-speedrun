#pragma once

#include <string>
#include <cstdint>

namespace GE::Particle
{
	struct CoreConfig
	{
		std::string imgFilePath = "";
		std::int16_t renderPriority = 0;
		int noOfParticle = 0;
		float life = 0.0;
	};
}