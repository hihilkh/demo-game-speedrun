#pragma once

namespace GE
{
	class GameLoopObject
	{
	public:
		virtual ~GameLoopObject() = default;

	protected:
		virtual void Awake() {}
		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
		virtual void OnEnable() {}
		virtual void OnDisable() {}
	};
}