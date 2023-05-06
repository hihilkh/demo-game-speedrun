#pragma once

namespace GE::Internal
{
	class GameLoopObject
	{
	public:
		virtual ~GameLoopObject() = default;

		virtual void Awake() {}
		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}

		bool GetEnable() const { return isEnable; }
		void SetEnable(bool isEnable) { this->isEnable = isEnable; }

	private:
		bool isEnable = true;
	};
}