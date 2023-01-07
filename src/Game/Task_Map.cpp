﻿#include "Task_Map.h"
#include "GameReference.h"
#include "Utils/Log.h"
#include "Task_GameCamera.h"
#include "GameReference.h"
#include "GameStatus.h"
#include "Utils/Math.h"
#include "Task/TaskConstant.h"
#include "Game/Task_Game.h"

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
		ML::Rect indexes = GetOverlappedMapChipIndexes(visibleRange);

		for (int y = indexes.top; y < indexes.bottom; ++y) {
			for (int x = indexes.left; x < indexes.right; ++x) {
				ML::Box2D draw(0, 0, CHIP_SIZE, CHIP_SIZE);	
				draw.Offset((x + mapChipLeftmostIndex) * CHIP_SIZE, (y + mapChipTopmostIndex) * CHIP_SIZE);	// chip のワールドポジション
				draw.Offset(mapChipCenterOffset);										// ローカルオフセット
				draw.Offset(-visibleRange.x, -visibleRange.y);							// カメラに合わせる
				this->res->Draw(this->arr[y][x], draw);
			}
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

		fin >> sizeX >> sizeY >> mapChipLeftmostIndex >> mapChipTopmostIndex;
		hitBase = ML::Box2D(
			mapChipCenterOffset.x + mapChipLeftmostIndex * CHIP_SIZE, 
			mapChipCenterOffset.y + mapChipTopmostIndex * CHIP_SIZE,
			sizeX * CHIP_SIZE,
			sizeY * CHIP_SIZE);

		for (int y = 0; y < sizeY; ++y) {
			for (int x = 0; x < sizeX; ++x) {
				fin >> this->arr[y][x];
			}
		}
		fin.close();

		return true;
	}

	ML::Rect Object::GetOverlappedMapChipIndexes(const ML::Box2D& hit) const
	{
		if (!this->hitBase.Hit(hit)) {
			return ML::Rect{ 0, 0, 0, 0 };
		}

		ML::Rect overlappedRect = {
			max(hit.x, hitBase.x),		// Left
			max(hit.y, hitBase.y),		// Top
			min(hit.x + hit.w, hitBase.x + hitBase.w) - 1,	// Right
			min(hit.y + hit.h, hitBase.y + hitBase.h) - 1,	// Bottom
		};

		ML::Rect result;
		result.left = Math::FloorDivide(overlappedRect.left - mapChipCenterOffset.x, CHIP_SIZE) - mapChipLeftmostIndex;
		result.top = Math::FloorDivide(overlappedRect.top - mapChipCenterOffset.y, CHIP_SIZE) - mapChipTopmostIndex;
		result.right = 1 + Math::FloorDivide(overlappedRect.right - mapChipCenterOffset.x, CHIP_SIZE) - mapChipLeftmostIndex;
		result.bottom = 1 + Math::FloorDivide(overlappedRect.bottom - mapChipCenterOffset.y, CHIP_SIZE) - mapChipTopmostIndex;

		return result;
	}

	bool Object::CheckHit(const ML::Box2D& hit) const
	{
		ML::Rect indexes = GetOverlappedMapChipIndexes(hit);

		//範囲内の障害物を探す
		for (int y = indexes.top; y < indexes.bottom; ++y) {
			for (int x = indexes.left; x < indexes.right; ++x) {
				if (8 <= this->arr[y][x]) {
					return true;
				}
			}
		}
		return false;
	}
#pragma endregion
}