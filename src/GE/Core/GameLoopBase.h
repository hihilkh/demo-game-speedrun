#pragma once

namespace GE::Internal
{
	class GameLoopBase
	{
	public:
		virtual ~GameLoopBase() = default;

		virtual void OnAwake() {}
		virtual void OnStart() {}
		virtual void OnUpdate() {}
		virtual void OnLateUpdate() {}
		// TODO : Temp
		// OnDestroy / Destroy

		bool GetEnable() const { return isEnable; }
		void SetEnable(bool isEnable) { this->isEnable = isEnable; }

	private:
		bool isEnable = true;
	};
}