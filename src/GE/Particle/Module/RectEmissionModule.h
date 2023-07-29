﻿#pragma once

#include "EmissionModule.h"
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Rect.h"

namespace GE::Particle
{
	class RectEmissionModule : public EmissionModule
	{
	public:
		explicit RectEmissionModule();

		void SetRect(float width, float height) { this->rect = Rect::FromCenter(width, height); }
		void SetRect(const Rect& rect) { this->rect = rect; }

	protected:
		void ApplyModule(Internal::ParticleComponent& particleComponent) override;

	private:
		Rect rect;
	};
}