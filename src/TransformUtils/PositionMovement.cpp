#include "GE/GEHeader.h"
#include "PositionMovement.h"

namespace TransformUtils
{
	PositionMovement::PositionMovement(GameObject& gameObject) :
		Component(gameObject)
	{
	}

	void PositionMovement::Update()
	{
		switch (moveState) {
			case MoveState::None:
				SetIsEnable(false);
				break;
			case MoveState::Moving:
				UpdateMove();
				break;
		}
	}

	void PositionMovement::UpdateMove()
	{
		bool hasFinished = false;
		float timeProgress = period == 0 ? 1 : (Time::GetTime() - startMovingTime) / period;

		if (timeProgress >= 1) {
			timeProgress = 1;
			hasFinished = true;
		}

		float progress = GE::Easing::Ease(timeProgress, easingType);
		Vector2 pos = Vector2::Lerp(from, to, progress);

		if (isLocalPos) {
			GetTransform().SetPos(pos);
		} else {
			GetTransform().SetWorldPos(pos);
		}

		if (hasFinished) {
			moveState = MoveState::None;
			SetIsEnable(false);
			std::function<void()> temp = onFinished;
			onFinished = nullptr;
			if (temp) {
				temp();
			}
		}
	}

	void PositionMovement::StartMoving(
		const Vector2& from,
		const Vector2& to,
		bool isLocalPos,
		float period,
		GE::Easing::Type easingType,
		std::function<void()> onFinished,
		bool isMoveBack,
		float moveBackWaitTime)
	{
		StopAllCoroutines();

		this->from = from;
		this->to = to;
		this->isLocalPos = isLocalPos;
		this->period = period;
		this->easingType = easingType;

		if (isMoveBack) {
			this->storedOnFinished = onFinished;
			this->onFinished = [this, moveBackWaitTime] {
				this->WaitAndNextAction(
					moveBackWaitTime,
					[this] { this->StartReturnMove(); }
				);
			};
		} else {
			this->storedOnFinished = nullptr;
			this->onFinished = onFinished;
		}

		moveState = MoveState::Moving;
		startMovingTime = Time::GetTime();
		SetIsEnable(true);
	}

	void PositionMovement::WaitAndNextAction(float waitTime, std::function<void()> nextAction)
	{
		moveState = MoveState::Waiting;
		SetIsEnable(true);

		StartCoroutine(GE::Yield::WaitSecond(waitTime), nextAction);
	}

	void PositionMovement::StartReturnMove()
	{
		Vector2 newFrom = to;
		Vector2 newTo = from;
		StartMoving(newFrom, newTo, isLocalPos, period, easingType, storedOnFinished);
	}
}