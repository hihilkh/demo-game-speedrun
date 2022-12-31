﻿#pragma once

#include "Task/ResourceBase.h"
#include "Task/ObjectBase.h"
#include "Task/TaskConstant.h"
#include "Common/Transform.h"

namespace GameCamera
{
	//タスクに割り当てるグループ名と固有名
	const string defGroupName(TaskConstant::TaskGroupName_Game);		//グループ名
	const string defName(TaskConstant::TaskName_GameCamera);			//タスク名

	class Object : public ObjectBase<Object>
	{
		friend ObjectBase<Object>;

	private:
		Object();

	public:
		virtual ~Object();

		void UpDate() override;			//「実行」１フレーム毎に行う処理
		void Render2D_AF() override;	//「2D描画」１フレーム毎に行う処理

	private:
		ML::Box2D visibleRange;
		ML::Point targetOffset;
		ML::Point currentCameraOffset;

		Transform::WP target;

	private:
		void UpdateTarget(const ML::Vec2& pos);
		void UpdateCameraOffset();

	public:
		// TODO : Study about getter overload
		ML::Box2D GetVisibleRange();
		const ML::Point& GetCameraOffset() const;

		void SetTarget(Transform::SP transform);
	};
}