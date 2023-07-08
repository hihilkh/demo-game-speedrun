#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"

namespace GE::UI
{
	class Text;
}

namespace TimeUtils
{
	class Timer;
}


namespace GameScene
{
	class GameTimerController : public Component
	{
	public:
		GameTimerController(GameObject& gameObject, TimeUtils::Timer& timer, GE::UI::Text& text);

		void Update() override;

		void StartTimer();
		void PauseTimer();
		float GetCountedTime() const;

	private:
		TimeUtils::Timer& timer;
		GE::UI::Text& text;
	};
}