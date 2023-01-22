#pragma once

#include "Task/ResourceBase.tpp"
#include "Task/ObjectBase.tpp"
#include "Common/Transform.h"

namespace Game::Camera
{
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
		const ML::Box2D& GetVisibleRange() const;
		const ML::Point& GetCameraOffset() const;

		void SetTarget(Transform::SP transform);
	};
}