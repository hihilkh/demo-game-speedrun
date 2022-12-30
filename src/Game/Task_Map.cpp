#include "Task_Map.h"
#include "GameReference.h"
#include "Utils/Log.h"
#include "Task_GameCamera.h"
#include "GameReference.h"
#include "GameStatus.h"
#include "Utils/Math.h"

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
		ObjectBaseWithResource<Object, Resource>(defGroupName, defName),
		isInitialized(false),
		mapChipCenterOffset(ML::Point{ -CHIP_SIZE / 2, -CHIP_SIZE / 2})
	{
		render2D_Priority[1] = 0.9f;
	}

	Object::~Object()
	{
	}

	void Object::UpDate()
	{
	}

	void Object::Render2D_AF()
	{
		if (!isInitialized) {
			return;
		}

		ML::Box2D visibleRange = camera->GetVisibleRange();
		if (!this->hitBase.Hit(visibleRange)) {
			return;
		}

		ML::Rect displayRect = {
			max(visibleRange.x, hitBase.x),		// Left
			max(visibleRange.y, hitBase.y),		// Top
			min(visibleRange.x + visibleRange.w, hitBase.x + hitBase.w) - 1,	// Right
			min(visibleRange.y + visibleRange.h, hitBase.y + hitBase.h) - 1,	// Bottom
		};

		int minIndexX, minIndexY, maxIndexX, maxIndexY;
		minIndexX = Math::FloorDivide(displayRect.left - mapChipCenterOffset.x, CHIP_SIZE) - leftIndex;
		minIndexY = Math::FloorDivide(displayRect.top - mapChipCenterOffset.y, CHIP_SIZE) - topIndex;
		maxIndexX = Math::FloorDivide(displayRect.right - mapChipCenterOffset.x, CHIP_SIZE) - leftIndex;
		maxIndexY = Math::FloorDivide(displayRect.bottom - mapChipCenterOffset.y, CHIP_SIZE) - topIndex;

		for (int y = minIndexY; y <= maxIndexY; ++y) {
			for (int x = minIndexX; x <= maxIndexX; ++x) {
				ML::Box2D draw(0, 0, CHIP_SIZE, CHIP_SIZE);	
				draw.Offset((x + leftIndex) * CHIP_SIZE, (y + topIndex) * CHIP_SIZE);	// chip のワールドポジション
				draw.Offset(mapChipCenterOffset);										// ローカルオフセット
				draw.Offset(-visibleRange.x, -visibleRange.y);							// カメラに合わせる
				this->res->Draw(this->arr[y][x], draw);
			}
		}
	}

	void Object::Initialize()
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

		fin >> sizeX >> sizeY >> leftIndex >> topIndex;
		hitBase = ML::Box2D(
			mapChipCenterOffset.x + leftIndex * CHIP_SIZE, 
			mapChipCenterOffset.y + topIndex * CHIP_SIZE,
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

	bool Object::CheckHit(const ML::Box2D& hit) const
	{
		// TODO
		return false;

		ML::Rect  r = { hit.x, hit.y, hit.x + hit.w, hit.y + hit.h };
		//矩形がマップ外に出ていたらサイズを変更する
		ML::Rect  m = {
			this->hitBase.x,
			this->hitBase.y,
			this->hitBase.x + this->hitBase.w,
			this->hitBase.y + this->hitBase.h
		};
		if (r.left < m.left) { r.left = m.left; }
		if (r.top < m.top) { r.top = m.top; }
		if (r.right > m.right) { r.right = m.right; }
		if (r.bottom > m.bottom) { r.bottom = m.bottom; }

		//ループ範囲調整
		int sx, sy, ex, ey;
		sx = r.left / 32;
		sy = r.top / 32;
		ex = (r.right - 1) / 32;
		ey = (r.bottom - 1) / 32;

		//範囲内の障害物を探す
		for (int y = sy; y <= ey; ++y) {
			for (int x = sx; x <= ex; ++x) {
				if (8 <= this->arr[y][x]) {
					return true;
				}
			}
		}
		return false;
	}
#pragma endregion
}