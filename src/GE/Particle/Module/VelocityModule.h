#pragma once

#include "Module.h"
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Vector2.h"

namespace GE::Particle
{
	class VelocityModule : public Module
	{
	public:
		explicit VelocityModule();

		void ApplyModule(GameObject& baseObject) override;

		void SetEmitAngleRange(float fromDegree, float toDegree) { emitAngleRange = Vector2(fromDegree, toDegree); }
		void SetEmitAngleRange(float constantDegree) { SetEmitAngleRange(constantDegree, constantDegree); }
		
		void SetEmitSpeedRange(float from, float to) { emitSpeedRange = Vector2(from, to); }
		void SetEmitSpeedRange(float constantSpeed) { SetEmitSpeedRange(constantSpeed, constantSpeed); }
		
		void SetAcceleration(float accelerationX, float accelerationY) { acceleration = Vector2(accelerationX, accelerationY); }
		void SetAcceleration(const Vector2& acceleration) { this->acceleration = acceleration; }

		const Vector2& GetAcceleration() const { return acceleration; }

	private:
		Vector2 emitAngleRange;
		Vector2 emitSpeedRange;
		Vector2 acceleration;
	};
}