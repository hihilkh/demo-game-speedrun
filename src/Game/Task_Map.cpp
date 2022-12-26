#include "Task_Map.h"

namespace Map
{
#pragma region Resource

	Resource::Resource()
	{
		chipImg = DG::Image::Create(GetImagePath(ResourceConstant::MapImage));

		for (int i = 0; i < ResourceConstant::NoOfMapChip; ++i) {
			int noInRow = ResourceConstant::NoOfMapChipInRow;
			int size = ResourceConstant::MapChipSize;
			int x = (i % noInRow);
			int y = (i / noInRow);
			
			chip[i] = ML::Box2D(x * size, y * size, size, size);
		}
	}

	Resource::~Resource()
	{
		chipImg.reset();
	}

	void Resource::Draw(int chipIndex, const ML::Box2D& draw)
	{
		chipImg->Draw(draw, chip[chipIndex]);
	}

#pragma endregion

#pragma region Object

	Object::Object() : ObjectBase<Object, Resource>(defGroupName, defName), isInitialized(false)
	{
		render2D_Priority[1] = 0.9f;
	}

	Object::~Object()
	{
		// TODO
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

		// TODO : Review code
		ML::Rect c = {
			visibleRange.x,
			visibleRange.y,
			visibleRange.x + visibleRange.w,
			visibleRange.y + visibleRange.h
		};
		ML::Rect m = {
			this->hitBase.x,
			this->hitBase.y,
			this->hitBase.x + this->hitBase.w,
			this->hitBase.y + this->hitBase.h
		};

		ML::Rect isr;
		isr.left = max(c.left, m.left);
		isr.top = max(c.top, m.top);
		isr.right = min(c.right, m.right);
		isr.bottom = min(c.bottom, m.bottom);

		int sx, sy, ex, ey;
		sx = isr.left / 32;
		sy = isr.top / 32;
		ex = (isr.right - 1) / 32;
		ey = (isr.bottom - 1) / 32;

		for (int y = sy; y <= ey; ++y) {
			for (int x = sx; x <= ex; ++x) {
				ML::Box2D  draw(0, 0, 32, 32);
				draw.Offset(x * 32, y * 32);	//表示位置を調整
				draw.Offset(-visibleRange.x, -visibleRange.y);
				this->res->Draw(this->arr[y][x], draw);
			}
		}
	}

	void Object::Initialize(GameCamera::Object::SP camera)
	{
		isInitialized = true;
		this->camera = camera;
	}

	bool Object::Load(const string& filePath)
	{
		ifstream fin(filePath);
		if (!fin) { return  false; }

		fin >> this->sizeX >> this->sizeY;
		this->hitBase = ML::Box2D(0, 0, this->sizeX * 32, this->sizeY * 32);

		for (int y = 0; y < this->sizeY; ++y) {
			for (int x = 0; x < this->sizeX; ++x) {
				fin >> this->arr[y][x];
			}
		}
		fin.close();

		return true;
	}

	void Object::AdjustCameraPos() const
	{
		// TODO
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