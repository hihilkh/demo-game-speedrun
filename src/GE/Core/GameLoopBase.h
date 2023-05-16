#pragma once

namespace GE::Internal
{
	class GameLoopBase
	{
	public:
		virtual ~GameLoopBase() = default;

#pragma region ゲームループ

		virtual void OnAwake() {}
		virtual void OnStart() {}
		virtual void OnUpdate() {}
		virtual void OnLateUpdate() {}
		// TODO : Temp
		// OnDestroy / Destroy

#pragma endregion

		bool GetEnable() const { return isEnable; }
		void SetEnable(bool isEnable) { this->isEnable = isEnable; }

	private:
		bool isEnable = true;
	};
}