#pragma once

namespace GE::Particle
{
	class CoreConfig
	{
	public:
		explicit CoreConfig(float life);

		float GetLife() const { return life; }

	private:
		float life;
	};
}