#pragma once

#include "Module.h"

namespace GE::Particle
{
	class CoreModule : public Module
	{
	public:
		explicit CoreModule();

		void ApplyModule(GameObject& baseObject) override;

		void SetLife(float life) { this->life = life; }
		float GetLife() const { return life; }

	private:
		float life;
	};
}