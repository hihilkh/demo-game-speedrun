#pragma warning(disable:4996)
#pragma once
//-------------------------------------------------------------------
//タイトル画面
//-------------------------------------------------------------------
#include "Task/ResourceBase.h"
#include "Task/ObjectBase.h"
#include "Task/TaskConstant.h"

namespace Title
{
	//タスクに割り当てるグループ名と固有名
	const string defGroupName(TaskConstant::TaskGroupName_Title);		//グループ名
	const string defName(TaskConstant::TaskName_Default);				//タスク名

	class Resource : public ResourceBase<Resource>
	{
		friend ResourceBase<Resource>;

	private:
		Resource();
	public:
		~Resource();

		DG::Image::SP img;
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

		int logoPosY;		//タイトル画像スクロール用カウンタ
	};
}