#pragma once

#include "Task/ResourceBase.h"
#include "Task/ObjectBase.h"
#include "Task/TaskConstant.h"
#include "Task_GameCamera.h"

#pragma region 前方宣言

namespace GameCamera { class Object; }

#pragma endregion

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
	class  Object : public  ObjectBaseWithResource<Object, Resource>
	{
		friend ObjectBase<Object>;

	private:
		Object();

	public:
		virtual ~Object();

		void UpDate() override;			//「実行」１フレーム毎に行う処理
		void Render2D_AF() override;	//「2D描画」１フレーム毎に行う処理

	private:
		int sizeX;
		int sizeY;
		int mapChipLeftmostIndex;
		int mapChipTopmostIndex;
		ML::Box2D hitBase;
		ML::Point mapChipCenterOffset;

		// TODO : Use SubMap with std::array
		int arr[100][100];

		shared_ptr<GameCamera::Object> camera;

		bool isInitialized;
		// TODO : bool isMapLoaded?

	private:
		string GetMapFilePath(int mapIndex) const;
		bool Load(const string& filePath);

		// TOOD : Use iterator and Map Chip class
		/// <returns>
		/// x 添字：Rect.leftからRect.rightまで（含まない）<para />
		/// y 添字：Rect.topからRect.bottomまで（含まない）
		/// </returns>
		ML::Rect GetOverlappedMapChipIndexes(const ML::Box2D& hit) const;

	public:
		void Initialize();
		bool CheckHit(const ML::Box2D& hit) const;
	};
}