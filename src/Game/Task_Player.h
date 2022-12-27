#pragma once

#include "Task/ResourceBase.h"
#include "Task/ObjectBase.h"
#include "Task/TaskConstant.h"
#include "CharaBase.h"
#include "Task_GameCamera.h"

namespace Player
{
	//タスクに割り当てるグループ名と固有名
	const string defGroupName(TaskConstant::TaskGroupName_Chara);		//グループ名
	const string defName(TaskConstant::TaskName_Player);				//タスク名

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

	class Object : public ObjectBaseWithResource<Object, Resource>, public CharaBase
	{
		friend ObjectBase<Object>;

	private:
		Object();

	public:
		virtual ~Object();

		void UpDate() override;			//「実行」１フレーム毎に行う処理
		void Render2D_AF() override;	//「2D描画」１フレーム毎に行う処理

	private:
		GameCamera::Object::SP camera;
		XI::GamePad::SP  controller;

		bool isInitialized;

	public:
		void Initizalize(GameCamera::Object::SP camera, Map::Object::SP map, const ML::Vec2& pos);

	};
}