#pragma once

namespace GE::Memory
{
	// 備考：
	// TはGE::Internal::Destroyableの派生クラスにしなければいけない。
	// でも、もしそのようなconceptを付けると、GESafePtr<T>の型の変数を宣言するとき、Tのヘッダーファイルも必要になってしまう。
	// そういうわけで、特にconceptを付けなかった。
	template<typename T>
	class GESafePtr
	{
	public:
#pragma region 初期化 / 代入

#define ADD_LISTENER() \
	if (*this) {\
		this->ptr->onDestroying.AddListener(&GESafePtr::OnPtrDestroyingHandler, *this);\
	}

#define REMOVE_LISTENER() \
	if (*this) {\
		this->ptr->onDestroying.RemoveListener(&GESafePtr::OnPtrDestroyingHandler, *this);\
	}

		GESafePtr() : ptr(nullptr) { }
		explicit GESafePtr(T* ptr) : ptr(ptr) { ADD_LISTENER(); }
		~GESafePtr() { REMOVE_LISTENER(); }

		GESafePtr(const GESafePtr& other) : ptr(other.Get()) { ADD_LISTENER(); }
		GESafePtr& operator=(const GESafePtr& other)
		{
			Reset(other.Get());
			return *this;
		}

		void Reset(T* ptr = nullptr)
		{
			REMOVE_LISTENER();
			this->ptr = ptr;
			ADD_LISTENER();
		}

#undef ADD_LISTENER
#undef REMOVE_LISTENER

#pragma endregion

		T* Get() const { return ptr; }
		T* operator->() const { return ptr; }
		T& operator*() const { return *ptr; }

		operator bool() const { return ptr != nullptr; }

	private:
		T* ptr;

	private:
		void OnPtrDestroyingHandler() { ptr = nullptr; }
	};
}