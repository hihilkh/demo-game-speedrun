#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"

namespace GE::UI
{
	class Text;
}

namespace Timing
{
	class Timer;
}


namespace GameScene
{
	class GameTimerController : public Component
	{
	public:
		GameTimerController(GameObject& gameObject, Timing::Timer& timer, GE::UI::Text& text);

		void Update() override;

		void StartTimer();
		void PauseTimer();
		float GetCountedTime() const;

	private:
		Timing::Timer& timer;
		GE::UI::Text& text;
	};
}