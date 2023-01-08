#pragma once

// TODO : Is it a good way to use PlayerConstant?
namespace PlayerConstant
{
	const int HitBaseWidth = 32;
	const int HitBaseHeight = 32;

	const float WalkSpeed = 5.0f;
	const float RunSpeed = 10.0f;

	const int PrepareRunningPeriod = 30;	// フレーム
	const float Deceleration = 0.4f;

	const int RenderWidth = 32;
	const int RenderHeight = 32;
}