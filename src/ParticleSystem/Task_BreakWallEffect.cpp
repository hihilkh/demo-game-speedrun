#include "Task_BreakWallEffect.h"
#include "Task/TaskConstant.h"
#include "Game/Task_GameCamera.h"
#include "Utils/Log.h"

namespace ParticleSystem::BreakWallEffect
{

#pragma region Resource

	Resource::Resource()
	{
		img = DG::Image::Create(GetImagePath(ResourceConstant::WallFragmentImage));
	}

	Resource::~Resource()
	{
	}

#pragma endregion

#pragma region Object

	Object::Object() :
		ObjectBaseWithResource<Object, Resource>(TaskConstant::TaskGroupName_ParticleSystem, TaskConstant::TaskName_Default),
		isPlaying(false),
		totalLife(0),
		remainingLife(0)
	{
		render2D_Priority[1] = 0.3f;

		camera = ge->GetTask<Game::Camera::Object>(TaskConstant::TaskGroupName_Game, TaskConstant::TaskName_GameCamera);
	}

	void Object::PostCreate()
	{
		ML::Box2D src = ML::Box2D(0, 0, 16, 16);
		ML::Box2D drawBase = ML::Box2D(-8, -8, 16, 16);

		particleConfig = make_shared<ParticleConfig>(res->img, src, drawBase, ML::Vec2(0.0f, 0.0f));
		particleConfig->randomPosHalfRange = 8.0f;
		particleConfig->emitAngleRange.x = 0.0f;
		particleConfig->emitAngleRange.y = 360.0f;
		particleConfig->emitSpeed = 1.0f;
		particleConfig->hasGravity = true;
	}

	Object::~Object()
	{
	}

	void Object::UpDate()
	{
		if (!isPlaying) {
			return;
		}

		--remainingLife;

		if (remainingLife <= 0) {
			this->Kill();
			return;
		}

		for (Particle& particle : particles) {
			particle.UpDate();
		}

	}

	void Object::Render2D_AF()
	{
		if (!isPlaying) {
			return;
		}

		if (!camera) {
			return;
		}

		const ML::Point& cameraOffset = camera->GetCameraOffset();
		float alpha = remainingLife / (float)totalLife;
		for (Particle& particle : particles) {
			particle.Render(cameraOffset, alpha);
		}
	}

	void Object::Play(const ML::Vec2& pos, int noOfParticle, int life)
	{
		GenerateParticles(pos, noOfParticle);
		totalLife = life;
		remainingLife = life;
		isPlaying = true;
	}

	void Object::GenerateParticles(const ML::Vec2& pos, int noOfParticles)
	{
		particles.reserve(noOfParticles);

		particleConfig->posBase = pos;

		for (int i = 0; i < noOfParticles; ++i) {
			particles.emplace_back(particleConfig);
		}
	}

#pragma endregion
}