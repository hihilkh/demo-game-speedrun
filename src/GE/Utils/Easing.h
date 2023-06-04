#pragma once

namespace GE::Easing
{
	enum class Type
	{
		InOutSine,
	};

	/// <summary>
	/// tを必ず[0,1]になってください
	/// </summary>
	float Ease(float t, Type type);

	/// <summary>
	/// tを自動的に[0,1]にClampする
	/// </summary>
	float BoundedEase(float t, Type type);
}