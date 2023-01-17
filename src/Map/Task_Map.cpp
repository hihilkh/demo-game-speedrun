#include "Task_Map.h"
#include "Utils/Log.h"
#include "Utils/Math.h"
#include "Task/TaskConstant.h"
#include "Game/GameReference.h"
#include "Game/Task_Game.h"
#include "Game/Task_GameCamera.h"
#include "Game/GameStatus.h"
#include "MapChipBase.h"

namespace Map
{
	extern MapChipBase::SP GenerateMapChip(MapChipType type, shared_ptr<Resource> res, const ML::Box2D& hitBase);

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
		ObjectBaseWithResource<Object, Resource>(TaskConstant::TaskGroupName_Map, TaskConstant::TaskName_Map),
		isInitialized(false),
		mapChipCenterOffset(ML::Point{ -CHIP_SIZE / 2, -CHIP_SIZE / 2})
	{
		render2D_Priority[1] = 0.9f;

		Game::Object::gameReady.AddListener(this, &Object::GameReadyEventHandler);
	}

	Object::~Object()
	{
		Game::Object::gameReady.RemoveListeners(this);
	}

	void Object::UpDate()
	{
	}

	void Object::Render2D_AF()
	{
		if (!isInitialized) {
			return;
		}

		const ML::Box2D& visibleRange = camera->GetVisibleRange();

		MapChipItContainer itContainer = GetOverlappedMapChipInterator(visibleRange);
		for (auto& mapChip : itContainer) {
			mapChip->Render(-visibleRange.x, -visibleRange.y);
		}
	}

	void Object::GameReadyEventHandler()
	{
		isInitialized = true;
		this->camera = Game::GameReference::GetGameCamera();

		Game::GameStatus::SP gameStatus = Game::GameReference::GetGameStatus();
		int mapIndex;
		if (gameStatus) {
			mapIndex = gameStatus->GetInitialMapIndex();
		}
		else {
			PrintWarning("GameStatusが取れない。mapIndexを1になる。");
			mapIndex = 1;
		}
		Load(GetMapFilePath(mapIndex));
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
		int typeInt;

		// TODO : study of flyweight(?) pattern instead of instantiate all?
		for (int y = 0; y < size.y; ++y) {
			for (int x = 0; x < size.x; ++x) {
				fin >> typeInt;
				arr[y][x] = typeInt;
				ML::Box2D mapChipHitBase = ML::Box2D(x * CHIP_SIZE, y * CHIP_SIZE, CHIP_SIZE, CHIP_SIZE);
				mapChipHitBase.Offset(hitBase.x, hitBase.y);

				mapChips.push_back(GenerateMapChip(static_cast<MapChipType>(typeInt), res, mapChipHitBase));
			}
		}

		return true;
	}

	Object::MapChipItContainer Object::GetOverlappedMapChipInterator(const ML::Box2D& hit)
	{
		if (!this->hitBase.Hit(hit)) {
			return MapChipItContainer(mapChips, size.x, ML::Box2D(0, 0, 0, 0));
		}

		ML::Rect overlappedRect = {
			max(hit.x, hitBase.x),		// Left
			max(hit.y, hitBase.y),		// Top
			min(hit.x + hit.w, hitBase.x + hitBase.w) - 1,	// Right
			min(hit.y + hit.h, hitBase.y + hitBase.h) - 1,	// Bottom
		};

		ML::Box2D iterateBox;
		iterateBox.x = Math::FloorDivide(overlappedRect.left - mapChipCenterOffset.x, CHIP_SIZE) - mapChipLeftmostIndex;
		iterateBox.y = Math::FloorDivide(overlappedRect.top - mapChipCenterOffset.y, CHIP_SIZE) - mapChipTopmostIndex;
		iterateBox.w = (Math::FloorDivide(overlappedRect.right - mapChipCenterOffset.x, CHIP_SIZE) - mapChipLeftmostIndex) - iterateBox.x + 1;
		iterateBox.h = (Math::FloorDivide(overlappedRect.bottom - mapChipCenterOffset.y, CHIP_SIZE) - mapChipTopmostIndex) - iterateBox.y + 1;

		return MapChipItContainer(mapChips, size.x, iterateBox);
	}

	bool Object::CheckHit(const ML::Box2D& hit)
	{
		MapChipItContainer itContainer = GetOverlappedMapChipInterator(hit);

		//範囲内の障害物を探す
		for (auto& mapChip : itContainer) {
			if (mapChip->GetType() == MapChipType::UnbreakableWall) {
				return true;
			}
		}

		return false;
	}
#pragma endregion
}