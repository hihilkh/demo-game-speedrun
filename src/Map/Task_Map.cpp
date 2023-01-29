#include "Task_Map.h"
#include "Utils/Log.h"
#include "Utils/Math.h"
#include "Task/TaskConstant.h"
#include "Game/GameEvent.h"
#include "Game/Task_GameCamera.h"
#include "Game/GameStatus.h"
#include "Chara/CharaBase.h"
#include "MapChip/MapChipBase.h"
#include "MapChipFactory.h"

namespace Map
{

#define CHIP_SIZE ResourceConstant::MapChipSize

#pragma region Resource

	Resource::Resource()
	{
		chipImg = DG::Image::Create(GetImagePath(ResourceConstant::MapImage));

		for (int i = 0; i < ResourceConstant::NoOfMapChip; ++i) {
			int noInRow = ResourceConstant::NoOfMapChipInRow;
			int x = (i % noInRow);
			int y = (i / noInRow);
			
			chip[i] = ML::Box2D(x * CHIP_SIZE, y * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE);
		}
	}

	Resource::~Resource()
	{
	}

	void Resource::Draw(int chipIndex, const ML::Box2D& draw)
	{
		chipImg->Draw(draw, chip[chipIndex]);
	}

#pragma endregion

#pragma region Object

	Object::Object() :
		ObjectBaseWithResource<Object, Resource>(TaskConstant::TaskGroupName_Map, TaskConstant::TaskName_Map, true),
		mapChipCenterOffset(ML::Point{ -CHIP_SIZE / 2, -CHIP_SIZE / 2}),
		mapChipLeftmostIndex(0),
		mapChipTopmostIndex(0),
		size(ML::Point(0, 0)),
		isInitialized(false)
	{
		render2D_Priority[1] = 0.9f;

		Game::gameReady.AddListener(this, &Object::GameReadyEventHandler);
	}

	Object::~Object()
	{
		Game::gameReady.RemoveListeners(this);

		ge->KillAll_G(TaskConstant::TaskGroupName_MapObject);
	}

	void Object::UpDate()
	{
	}

	void Object::Render2D_AF()
	{
		if (!isInitialized) {
			return;
		}

		auto cameraSP = camera.lock();
		if (!cameraSP) {
			return;
		}

		const ML::Box2D& visibleRange = cameraSP->GetVisibleRange();

		vector<MapChipBase::SP> mapChips = GetOverlappedMapChipIterator(visibleRange);
		for (MapChipBase::SP& mapChip : mapChips) {
			mapChip->Render(-visibleRange.x, -visibleRange.y);
		}
	}

	void Object::GameReadyEventHandler()
	{
		isInitialized = true;

		camera = ge->GetTask<Game::Camera::Object>(TaskConstant::TaskGroupName_Game, TaskConstant::TaskName_GameCamera);

		Load(GetMapFilePath(Game::GameStatus::MapIndex));
	}

	string Object::GetMapFilePath(int mapIndex) const
	{
		using namespace ResourceConstant;
		return MapFolder + MapFileNamePrefix + to_string(mapIndex) + MapFileNameExtension;
	}

	bool Object::Load(const string& filePath)
	{
		ifstream fin(filePath);
		if (!fin) { return false; }

		fin >> size.x >> size.y >> mapChipLeftmostIndex >> mapChipTopmostIndex;
		hitBase = ML::Box2D(
			mapChipCenterOffset.x + mapChipLeftmostIndex * CHIP_SIZE, 
			mapChipCenterOffset.y + mapChipTopmostIndex * CHIP_SIZE,
			size.x * CHIP_SIZE,
			size.y * CHIP_SIZE);

		mapChips.reserve(size.x * size.y);
		int typeId;

		// TODO : study of flyweight(?) pattern instead of instantiate all?
		for (int y = 0; y < size.y; ++y) {
			for (int x = 0; x < size.x; ++x) {
				fin >> typeId;
				ML::Box2D mapChipHitBase = ML::Box2D(x * CHIP_SIZE, y * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE);
				mapChipHitBase.Offset(hitBase.x, hitBase.y);

				mapChips.push_back(GenerateMapChip(typeId, res, mapChipHitBase));
				GenerateMapObject(typeId, mapChipHitBase);
			}
		}

		return true;
	}

	vector<MapChipBase::SP> Object::GetOverlappedMapChipIterator(const ML::Box2D& hit)
	{
		if (!this->hitBase.Hit(hit)) {
			return vector<MapChipBase::SP>();
		}

		ML::Rect overlappedRect = {
			max(hit.x, hitBase.x),		// Left
			max(hit.y, hitBase.y),		// Top
			min(hit.x + hit.w, hitBase.x + hitBase.w) - 1,	// Right
			min(hit.y + hit.h, hitBase.y + hitBase.h) - 1,	// Bottom
		};

		// LeftからRightまで(含む)
		// TopからBottomまで(含む)
		ML::Rect includedRect;
		includedRect.left = Math::FloorDivide(overlappedRect.left - mapChipCenterOffset.x, CHIP_SIZE) - mapChipLeftmostIndex;
		includedRect.top = Math::FloorDivide(overlappedRect.top - mapChipCenterOffset.y, CHIP_SIZE) - mapChipTopmostIndex;
		includedRect.right = Math::FloorDivide(overlappedRect.right - mapChipCenterOffset.x, CHIP_SIZE) - mapChipLeftmostIndex;
		includedRect.bottom = Math::FloorDivide(overlappedRect.bottom - mapChipCenterOffset.y, CHIP_SIZE) - mapChipTopmostIndex;

		vector<MapChipBase::SP> result = vector<MapChipBase::SP>();
		result.reserve((includedRect.right - includedRect.left + 1) * (includedRect.bottom - includedRect.top + 1));
		for (int y = includedRect.top; y <= includedRect.bottom; ++y) {
			for (int x = includedRect.left; x <= includedRect.right; ++x) {
				result.push_back(mapChips[y * size.x + x]);
			}
		}

		return result;
	}

	bool Object::CheckCollision(const Chara::CharaBase& chara)
	{
		ML::Box2D hitBox = chara.GetCurrentHitBox();
		vector<MapChipBase::SP> mapChips = GetOverlappedMapChipIterator(hitBox);

		//範囲内の障害物を探す、やりとりをする
		bool isHit = false;
		for (auto& mapChip : mapChips) {
			if (!mapChip->GetIsWalkable()) {
				mapChip->CollideWithChara(chara);
				isHit = true;
			}
		}

		return isHit;
	}

	void Object::CheckTrigger(Chara::CharaBase& chara)
	{
		// TODO : 今GetOverlappedMapChipIteratorは無駄にした。CheckCollisionからmapChipsを渡すことができるか。
		ML::Box2D hitBox = chara.GetCurrentHitBox();
		vector<MapChipBase::SP> mapChips = GetOverlappedMapChipIterator(hitBox);

		for (MapChipBase::SP& mapChip : mapChips) {
			mapChip->TriggerByChara(chara);
		}
	}
#pragma endregion
}