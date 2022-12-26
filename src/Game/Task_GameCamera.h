#pragma once

#include "Task/ResourceBase.h"
#include "Task/ObjectBase.h"
#include "Task/TaskConstant.h"

namespace GameCamera
{
	//タスクに割り当てるグループ名と固有名
	const string defGroupName(TaskConstant::TaskGroupName_Game);		//グループ名
	const string defName(TaskConstant::TaskName_GameCamera);					//タスク名

	class Resource : public ResourceBase<Resource>
	{
		friend ResourceBase<Resource>;

	private:
		Resource();
	public:
		~Resource();
	};

	class Object : public ObjectBase<Object, Resource>
	{
		friend ObjectBase<Object, Resource>;

	private:
		Object();

	public:
		virtual ~Object();

		void UpDate() override;			//「実行」１フレーム毎に行う処理
		void Render2D_AF() override;	//「2D描画」１フレーム毎に行う処理

	private:
		ML::Box2D visibleRange;
		int targetOffsetX;
		int targetOffsetY;
		ML::Point currentCameraOffset;

	private:
		void UpdateCameraOffset();

	public:
		// TODO : Study about getter overload
		ML::Box2D GetVisibleRange();
		const ML::Point& GetCameraOffset() const;

		void UpdateTarget(const ML::Vec2& pos);
	};
}