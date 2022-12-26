#pragma once

#include <GameEngine_Ver3_83.h>
#include <cassert>
#include "MyPG.h"

template<typename T, typename ResourceClass>
class ObjectBase : public BTask
{
protected:
	ObjectBase(string taskGroupName, string taskName, bool isDetectible = false)
	{
		__super::Initialize(taskGroupName, taskName, isDetectible);
		this->res = ResourceClass::Create();
	}

public:
	virtual ~ObjectBase() {}

	typedef shared_ptr<T> SP;
	typedef weak_ptr<T> WP;

	shared_ptr<ResourceClass> res;

	//¶¬‘‹Œû ˆø”‚Ítrue‚Åƒ^ƒXƒNƒVƒXƒeƒ€‚Ö©“®“o˜^
	static SP Create(bool flagGameEnginePushBack)
	{
		SP ob = SP(new T());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack) {
				ge->PushBack(ob);//ƒQ[ƒ€ƒGƒ“ƒWƒ“‚É“o˜^
			}
			return  ob;
		}

		assert(false && "Create ¸”s");
		return nullptr;
	}
};