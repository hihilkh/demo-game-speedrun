#pragma once

#include <GameEngine_Ver3_83.h>
#include "ResourceConstant.h"

template<typename T>
class ResourceBase : public BResource
{
private:
	// Initialize() �̑���ɁA�R���X�g���N�^�ŏ���������
	bool Initialize() override { return true; }
	// Finalize() �̑���ɁA�f�X�g���N�^�Ń��\�[�X�̉��������
	bool Finalize() override { return true; }

protected:
	ResourceBase() {}

public:
	virtual ~ResourceBase() {}

	typedef shared_ptr<T> SP;
	typedef weak_ptr<T> WP;
	static WP instance;

	static SP Create()
	{
		if (auto sp = instance.lock()) {
			return sp;
		}
		else {
			sp = SP(new T());
			if (sp) {
				instance = sp;
			}

			return sp;
		}
	}

	const string GetImagePath(const string& fileName) const
	{
		return ResourceConstant::ImageFolder + fileName;
	}
};

template<typename T>
weak_ptr<T>  ResourceBase<T>::instance;