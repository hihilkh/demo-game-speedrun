#pragma once
//-------------------------------------------------------------------
//エンディング
//-------------------------------------------------------------------
#include "Task/ResourceBase.tpp"
#include "Task/ObjectBase.tpp"

namespace Ending
{
	class Resource : public ResourceBase<Resource>
	{
		friend ResourceBase<Resource>;

	private:
		Resource();
	public:
		~Resource();

		DG::Image::SP img;
	};

	class Object : public ObjectBaseWithResource<Object, Resource>
	{
		friend ObjectBase<Object>;

	private:
		Object();

	public:
		virtual ~Object();

		void UpDate() override;			//「実行」１フレーム毎に行う処理
		void Render2D_AF() override;	//「2D描画」１フレーム毎に行う処理

		int logoPosY;		//"エンディング画像スクロール用カウンタ
	};
}