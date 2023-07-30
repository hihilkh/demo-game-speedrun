#include "CoreConfig.h"

namespace GE::Particle
{
	CoreConfig::CoreConfig(const std::string& imgFilePath, std::int16_t renderPriority, int noOfParticle, float life) :
		imgFilePath(imgFilePath),
		renderPriority(renderPriority),
		noOfParticle(noOfParticle),
		life(life)
	{
	}
}

