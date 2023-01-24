#pragma once

#include "Task/ResourceBase.tpp"
#include "Task/ObjectBase.tpp"

#pragma region 前方宣言

namespace Game::Camera { class Object; }
namespace Animation { class Animator; }

#pragma endregion

// TOOD : 基底クラスを作成
namespace Goal
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
		ML::Point pos;
		ML::Box2D hitBase;
		ML::Box2D renderBase;

		shared_ptr<Game::Camera::Object> camera;
		unique_ptr<Animation::Animator> animator;

	public:
		void Init(int posX, int posY);
	};
}