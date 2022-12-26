#pragma once

#include "Task/ResourceBase.h"
#include "Task/ObjectBase.h"
#include "Task/TaskConstant.h"
#include "Task_GameCamera.h"

namespace Map
{
	//タスクに割り当てるグループ名と固有名
	const string defGroupName(TaskConstant::TaskGroupName_Map);		//グループ名
	const string defName(TaskConstant::TaskName_Map);				//タスク名
	//-------------------------------------------------------------------
	class Resource : public ResourceBase<Resource>
	{
		friend ResourceBase<Resource>;

	private:
		Resource();
	public:
		~Resource();

	private:
		ML::Box2D chip[ResourceConstant::NoOfMapChip];

	public:
		DG::Image::SP chipImg;
		void Draw(int chipIndex, const ML::Box2D& draw);
	};
	//-------------------------------------------------------------------
	class  Object : public  ObjectBase<Object, Resource>
	{
		friend ObjectBase<Object, Resource>;

	private:
		Object();

	public:
		virtual ~Object();

		void UpDate() override;			//「実行」１フレーム毎に行う処理
		void Render2D_AF() override;	//「2D描画」１フレーム毎に行う処理

	private:
		int sizeX;
		int sizeY;
		ML::Box2D hitBase;

		int  arr[100][100];

		GameCamera::Object::SP camera;

		bool isInitialized;
		// TODO : bool isMapLoaded?

	public:
		void Initialize(GameCamera::Object::SP camera);
		bool Load(const string& filePath);
		void AdjustCameraPos() const;
		bool CheckHit(const ML::Box2D& hit) const;
	};
}