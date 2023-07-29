#pragma once

namespace GE::Particle
{
	namespace Internal
	{
		class ParticleComponent;
	}

	class Module
	{
		friend class ParticleSystem;

	public:
		explicit Module() = default;
		virtual ~Module() = default;

	protected:
		virtual void ApplyModule(Internal::ParticleComponent& particleComponent) = 0;
	};
}