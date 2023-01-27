#include "Particle.h"
#include "ParticleConstant.h"

namespace ParticleSystem
{
	Particle::Particle(ParticleConfig::SP config) :
		config(config),
		pos(config->GetRandomPos()),
		imgRotation(config->GetRandomImgRotation()),
		imgRotateCenter(config->GetImgRotationCenter()),
		moveVec(config->GetRandomMoveVec())
	{
	}

	Particle::~Particle()
	{
	}

	void Particle::UpDate()
	{
		pos += moveVec;

		if (config->hasGravity) {
			moveVec.y += Constant::Gravity;
		}
	}

	void Particle::Render(const ML::Point& cameraOffset, float alpha)
	{
		ML::Box2D draw = config->drawBase.OffsetCopy(pos);
		draw.Offset(cameraOffset);

		config->img->Rotation(imgRotation, imgRotateCenter);
		config->img->Draw(draw, config->src, ML::Color(alpha, 1.0f, 1.0f, 1.0f));
	}
}