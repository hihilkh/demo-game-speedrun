#pragma once

#include <GameEngine_Ver3_83.h>
#include <cassert>
#include "MyPG.h"
#include "Utils/Log.h"

template<typename T>
class ObjectBase : public BTask
{
protected:
	ObjectBase(string taskGroupName, string taskName, bool isDetectible = false)
	{
		__super::Initialize(taskGroupName, taskName, isDetectible);
	}

public:
	virtual ~ObjectBase() {}

	typedef shared_ptr<T> SP;
	typedef weak_ptr<T> WP;

	//ê∂ê¨ëãå˚ à¯êîÇÕtrueÇ≈É^ÉXÉNÉVÉXÉeÉÄÇ÷é©ìÆìoò^
	static SP Create(bool flagGameEnginePushBack)
	{
		SP ob = SP(new T());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack) {
				ge->PushBack(ob);//ÉQÅ[ÉÄÉGÉìÉWÉìÇ…ìoò^
			}
			return  ob;
		}

		assert(false && "Create é∏îs");
		return nullptr;
	}
};

template<typename T, typename ResourceClass>
class ObjectBaseWithResource : public ObjectBase<T>
{

protected:
	ObjectBaseWithResource(string taskGroupName, string taskName, bool isDetectible = false) : ObjectBase<T>(taskGroupName, taskName, isDetectible)
	{
		this->res = ResourceClass::Create();
	}

public:
	virtual ~ObjectBaseWithResource() {}

	shared_ptr<ResourceClass> res;
};