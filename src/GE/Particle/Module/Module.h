#pragma once

namespace GE::Particle
{
	namespace Internal
	{
		class ParticleComponent;
	}

	class Module
	{
		friend class ModuleSet;

	public:
		virtual ~Module() = default;

	protected:
		virtual void ApplyModule(Internal::ParticleComponent& particleComponent) const = 0;
	};
}