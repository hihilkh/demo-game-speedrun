#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"
#include <stdint.h>

namespace TimeUtils
{
	class Timer : public Component
	{
	public:
		enum class State : std::uint8_t
		{
			Stopped,
			Started,
			Paused,
		};

	public:
		explicit Timer(GameObject& gameObject);

		bool StartTimer();
		bool PauseTimer();
		bool UnpauseTimer();
		void ResetTimer();

		State getState() const { return state; }
		float GetCountedTime() const { return countedTime; }

	protected:
		void Update() override;

	private:
		State state;
		float countedTime;
	};
}