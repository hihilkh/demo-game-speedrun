#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"
#include <functional>
#include "GE/DataType/Vector2.h"
#include "GE/Utils/Easing.h"


namespace TransformUtils
{
	class PositionMovement : public Component
	{
	private:
		enum class MoveState : std::uint8_t
		{
			None,
			Moving,
			Waiting,
		};

	public:
		explicit PositionMovement(GameObject& gameObject);

		void StartMoving(
			const Vector2& from, 
			const Vector2& to, 
			bool isLocalPos,
			float period,
			GE::Easing::Type easingType,
			std::function<void()> onFinished = nullptr,
			bool isMoveBack = false,
			float moveBackWaitTime = 0.0f);

	protected:
		void Update() override;

	private:
		MoveState moveState = MoveState::None;
		Vector2 from = Vector2::zero;
		Vector2 to = Vector2::zero;
		bool isLocalPos = false;
		float period = 0.0f;
		float startMovingTime = 0.0f;
		GE::Easing::Type easingType = static_cast<GE::Easing::Type>(0);
		std::function<void()> onFinished = nullptr;
		std::function<void()> storedOnFinished = nullptr;

	private:
		void UpdateMove();

		void WaitAndNextAction(float waitTime, std::function<void()> onFinished);
		void StartReturnMove();
	};
}