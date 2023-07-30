#pragma once

#include <string>
#include <cstdint>

namespace GE::Particle
{
	struct CoreConfig
	{
		std::string imgFilePath;
		std::int16_t renderPriority;
		int noOfParticle;
		float life;

		CoreConfig(const std::string& imgFilePath, std::int16_t renderPriority, int noOfParticle, float life);
	};
}