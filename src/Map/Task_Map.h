#pragma once

#include "Task/ResourceBase.tpp"
#include "Task/ObjectBase.tpp"
#include "Game/Task_GameCamera.h"

#pragma region 前方宣言

namespace Game::Camera { class Object; }
namespace Map { class MapChipBase; }
namespace Chara { class CharaBase; }

#pragma endregion

namespace Map
{
	class Resource : public ResourceBase<Resource>
	{
		friend ResourceBase<Resource>;

	private:
		Resource();
	public:
		~Resource();

	public:
		DG::Image::SP chipImg;
	};
	//-------------------------------------------------------------------
	class Object : public ObjectBaseWithResource<Object, Resource>
	{
		friend ObjectBase<Object>;

	private:
		Object();

	public:
		~Object();

		void UpDate() override;			//「実行」１フレーム毎に行う処理
		void Render2D_AF() override;	//「2D描画」１フレーム毎に行う処理

	private:
		ML::Box2D hitBase;

		int mapChipLeftmostIndex;
		int mapChipTopmostIndex;
		ML::Point size;
		vector<shared_ptr<MapChipBase>> mapChips;

		weak_ptr<Game::Camera::Object> camera;

		bool isInitialized;


	private:

		vector<shared_ptr<MapChipBase>> GetOverlappedMapChipIterator(const ML::Box2D& hit);

	public:
		bool CheckCollision(const Chara::CharaBase& chara);
		void CheckTrigger(Chara::CharaBase& chara);
	};
}