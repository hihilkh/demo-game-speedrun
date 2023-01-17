#pragma once

#include <vector>
#include <myLib.h>

// TODO : Const Iteratorを追加？
template<typename T>
class BoxIteratorContainer
{
public:
	BoxIteratorContainer(std::vector<T>& srcContainer, int containerWidth, const ML::Box2D& iterateBox) :
		containerWidth(containerWidth),
		iteratorWidth(iterateBox.w)
	{
		beginPtr = &(srcContainer[iterateBox.y * containerWidth + iterateBox.x]);
		endPtr = beginPtr + iterateBox.h * containerWidth;
	}

	~BoxIteratorContainer() {}

private:
	int containerWidth;
	int iteratorWidth;

	T* beginPtr;
	T* endPtr;

#pragma region Iterator

public:
	struct Iterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

	private:
		pointer ptr;
		int containerWidth;
		int iteratorWidth;

		int widthCounter;

	public:
		Iterator(pointer ptr, int containerWidth, int iteratorWidth) :
			ptr(ptr),
			containerWidth(containerWidth),
			iteratorWidth(iteratorWidth),
			widthCounter(0)
		{
		}

		reference operator*() const { return *ptr; }
		pointer operator->() { return ptr; }

		Iterator& operator++() {
			++widthCounter;
			if (widthCounter < iteratorWidth) {
				++ptr;
			}
			else {
				widthCounter = 0;
				ptr += containerWidth - iteratorWidth + 1;
			}
			return *this;
		}
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

		friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; }
		friend bool operator!= (const Iterator& a, const Iterator& b) { return !(a == b); }
	};

#pragma endregion

public:
	Iterator begin() { return Iterator(beginPtr, containerWidth, iteratorWidth); }
	Iterator end() { return Iterator(endPtr, 0, 0); }
};