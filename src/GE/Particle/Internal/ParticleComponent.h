#pragma once

#include "GE/Core/Component.h"

namespace GE
{
	class GameObject;
}

namespace GE::Particle
{
	class CoreConfig;
}

namespace GE::Particle::Internal
{
	class ParticleComponent : public Component
	{
	public:
		ParticleComponent(GameObject& gameObject, const CoreConfig& coreConfig);

		template<typename F>
		void AddUpdateFunc(F&& func);

	protected:
		void Update() override;

	private:
		const CoreConfig& coreConfig;
		float startTime;

		std::vector<std::function<void(GameObject&, float)>> updateFuncArray;
	};

	template<typename F>
	void ParticleComponent::AddUpdateFunc(F&& func)
	{
		updateFuncArray.emplace_back(std::forward<F>(func));
	}
}