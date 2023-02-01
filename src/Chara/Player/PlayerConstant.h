#pragma once

#include <myLib.h>

// TODO : このスクリプトはいいか？悪いか？
namespace Player::Constant
{
	const ML::Box2D HitBase = ML::Box2D(-8, -4, 16, 8);
	const ML::Box2D RenderBase = ML::Box2D(-16, -32, 32, 32);

	const float WalkSpeed = 5.0f;
	const float RunSpeed = 10.0f;
	const float CrashSpeed = 7.0f;

	const int PrepareRunningPeriod = 20;	// フレーム
	const float Deceleration = 0.4f;

	const int FallbackPeriod = 30;	// フレーム
	const float FallbackMaxHeight = 16.0f;
	const float FallbackBackSpeed = 3.0f;
}