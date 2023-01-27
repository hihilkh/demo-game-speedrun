#pragma once

#include "ParticleConfig.h"

namespace ParticleSystem
{
	// TODO : Particle もタスクになるか？
	class Particle
	{
	public:
		Particle(ParticleConfig::SP config);
		~Particle();

	private:
		ParticleConfig::SP config;

		ML::Vec2 pos;
		float imgRotation;
		ML::Vec2 imgRotateCenter;
		ML::Vec2 moveVec;

	public:
		void UpDate();
		// TODO : カメラもParticleConfigに入れるか？
		void Render(const ML::Point& cameraOffset, float alpha);

	};
}