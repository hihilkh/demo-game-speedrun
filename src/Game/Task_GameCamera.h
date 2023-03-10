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

		bool isPerformingZoom;
		ML::Point performZoomFrom;
		ML::Point performZoomTo;
		std::function<void()> onFinishedPerformZoom;
		int currentPerformZoomCount;


	private:
		void UpdateTarget();
		void UpdateCameraPos(int targatX, int targetY);
		void UpdateCameraOffset();
		void UpdateZoom();

	public:
		const ML::Box2D& GetVisibleRange() const;
		const ML::Point& GetCameraOffset() const;

		void SetTarget(Transform::WP transform);

		void PerformZoom(const ML::Point& from, const ML::Point& to, std::function<void()> onFinished = nullptr);
	};
}