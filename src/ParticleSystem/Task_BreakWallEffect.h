#pragma once

#include "Task/ResourceBase.tpp"
#include "Task/ObjectBase.tpp"
#include "Particle.h"

#pragma region 前方宣言

namespace Game::Camera { class Object; }

#pragma endregion

// TODO : 基底クラスを作成
// TODO : 今ParticleConfigはshared_ptrの形でParticles全体シェアしているので、TaskごとにPlay一回しかできない
namespace ParticleSystem::BreakWallEffect
{
	class Resource : public ResourceBase<Resource>
	{
		friend ResourceBase<Resource>;

	private:
		Resource();
	public:
		~Resource();

	public:
		DG::Image::SP img;
	};
	//-------------------------------------------------------------------
	class Object : public ObjectBaseWithResource<Object, Resource>
	{
		friend ObjectBase<Object>;

	private:
		Object();

	protected:
		void PostCreate() override;

	public:
		~Object();

		void UpDate() override;			//「実行」１フレーム毎に行う処理
		void Render2D_AF() override;	//「2D描画」１フレーム毎に行う処理

	private:
		shared_ptr<Game::Camera::Object> camera;
		ParticleConfig::SP particleConfig;
		vector<Particle> particles;
		bool isPlaying;
		int totalLife;
		int remainingLife;

	private:
		void GenerateParticles(const ML::Vec2& pos, int noOfParticles);

	public:

		/// <param name="pos">再生位置</param>
		/// <param name="noOfParticle">パーティクルの数</param>
		/// <param name="life">フレーム単位</param>
		void Play(const ML::Vec2& pos, int noOfParticle, int life);
	};
}