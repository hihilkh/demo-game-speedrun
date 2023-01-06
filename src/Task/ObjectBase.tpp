#pragma once

#include <GameEngine_Ver3_83.h>
#include <cassert>
#include "MyPG.h"

template<typename T>
class ObjectBase : public BTask
{
protected:
	ObjectBase(string taskGroupName, string taskName, bool isDetectible = false)
	{
		__super::Initialize(taskGroupName, taskName, isDetectible);
	}

	virtual void PostCreate() {}

public:
	virtual ~ObjectBase() {}

	typedef shared_ptr<T> SP;
	typedef weak_ptr<T> WP;

	//生成窓口 引数はtrueでタスクシステムへ自動登録
	static SP Create(bool flagGameEnginePushBack)
	{
		SP ob = SP(new T());

		assert(ob && "Createタスクオブジェクト失敗");

		ob->me = ob;
		if (flagGameEnginePushBack) {
			ge->PushBack(ob);//ゲームエンジンに登録
		}

		ob->PostCreate();
		return  ob;
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

protected:
	shared_ptr<ResourceClass> res;
};