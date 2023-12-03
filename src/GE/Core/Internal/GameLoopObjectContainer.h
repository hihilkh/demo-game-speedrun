#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include <utility>
#include "GE/Debug/Log.h"
#include "GE/Utils/GEConcept.h"

namespace GE::Internal
{
	template<GameLoopObject T>
	class GameLoopObjectContainer
	{
	public:
		template<typename Derived = T, typename... Args>
		T& Add(bool isAwakeImmediate, Args&&... args);
		void Remove(const T& object);

#pragma region ゲームループ
		void OnAwake();
		bool OnStartUnstarted();
		void OnUpdate();
		void OnLateUpdate();
		void OnPreDestroy();
#pragma endregion

	private:
		std::vector<std::unique_ptr<T>> objects_Started;
		std::vector<std::unique_ptr<T>> objects_Unstarted;

#pragma region SimpleIterator

	// 備考：
	// SimpleIteratorとSimpleConstIteratorの仕組みは本当に簡単だ。
	// 簡単というより、危険だ。
	// コードを簡潔になるために使っているけど、運用を広げるべきではない。
	// そういうわけで、一般的な命名(iteratorとか、begin()とか)ではない。
	public:
		struct SimpleIterator
		{
			SimpleIterator(GameLoopObjectContainer& container, std::size_t index) : container(container), index(index) {}

			std::unique_ptr<T>& operator*() const
			{
				if (index < container.objects_Started.size()) {
					return container.objects_Started[index];
				} else {
					return container.objects_Unstarted[index - container.objects_Started.size()];
				}
			}

			SimpleIterator& operator++() { 
				++index;
				return *this; 
			}

			SimpleIterator operator++(int) { 
				SimpleIterator tmp = *this; 
				++(*this); 
				return tmp; 
			}

			friend bool operator== (const SimpleIterator& a, const SimpleIterator& b) { return a.index == b.index; };
			friend bool operator!= (const SimpleIterator& a, const SimpleIterator& b) { return !(a == b); };

		private:
			GameLoopObjectContainer& container;
			std::size_t index;
		};

		struct SimpleConstIterator
		{
			SimpleConstIterator(const GameLoopObjectContainer& container, std::size_t index) : container(container), index(index) {}

			const std::unique_ptr<T>& operator*() const
			{
				if (index < container.objects_Started.size()) {
					return container.objects_Started[index];
				} else {
					return container.objects_Unstarted[index - container.objects_Started.size()];
				}
			}

			SimpleConstIterator& operator++()
			{
				++index;
				return *this;
			}

			SimpleConstIterator operator++(int)
			{
				SimpleConstIterator tmp = *this;
				++(*this);
				return tmp;
			}

			friend bool operator== (const SimpleConstIterator& a, const SimpleConstIterator& b) { return a.index == b.index; };
			friend bool operator!= (const SimpleConstIterator& a, const SimpleConstIterator& b) { return !(a == b); };

		private:
			const GameLoopObjectContainer& container;
			std::size_t index;
		};

		SimpleIterator SimpleBegin() { return SimpleIterator(*this, 0); }
		SimpleIterator SimpleEnd() { return SimpleIterator(*this, objects_Started.size() + objects_Unstarted.size()); }
		SimpleIterator SimpleBegin_Started() { return SimpleBegin(); }
		SimpleIterator SimpleEnd_Started() { return SimpleIterator(*this, objects_Started.size()); }
		SimpleIterator SimpleBegin_Unstarted() { return SimpleEnd_Started(); }
		SimpleIterator SimpleEnd_Unstarted() { return SimpleEnd(); }

		SimpleConstIterator SimpleBegin() const { return SimpleConstIterator(*this, 0); }
		SimpleConstIterator SimpleEnd() const { return SimpleConstIterator(*this, objects_Started.size() + objects_Unstarted.size()); }
		SimpleConstIterator SimpleBegin_Started() const { return SimpleBegin(); }
		SimpleConstIterator SimpleEnd_Started() const { return SimpleConstIterator(*this, objects_Started.size()); }
		SimpleConstIterator SimpleBegin_Unstarted() const { return SimpleEnd_Started(); }
		SimpleConstIterator SimpleEnd_Unstarted() const { return SimpleEnd(); }

#pragma endregion

#pragma region deprecated

	/*
	public:
		static void Transfer(const T& object, GameLoopObjectContainer& from, GameLoopObjectContainer& to);
	*/

#pragma endregion
	};



#pragma region テンプレート定義

	template<GameLoopObject T>
		template<typename Derived, typename... Args>
	T& GameLoopObjectContainer<T>::Add(bool isAwakeImmediate, Args&&... args)
	{
		T& element = *(objects_Unstarted.emplace_back(std::make_unique<Derived>(std::forward<Args>(args)...)));
		if (isAwakeImmediate) {
			element.OnAwake();
		}
		return element;
	}

	template<GameLoopObject T>
	void GameLoopObjectContainer<T>::Remove(const T& object)
	{
		std::vector<std::unique_ptr<T>>* lists[] = {
			&objects_Started,
			&objects_Unstarted,
		};

		for (auto list : lists) {
			auto target = std::find_if(
				list->begin(),
				list->end(),
				[&object](const auto& contained) { return *contained == object; });

			if (target != list->end()) {
				list->erase(target);
				return;
			}
		}

		DEBUG_LOG_WARNING("GameLoopObjectContainer::Remove失敗：objectが見つけられない。");
	}

	template<GameLoopObject T>
	void GameLoopObjectContainer<T>::OnAwake()
	{
		for (auto it = SimpleBegin_Unstarted(), itEnd = SimpleEnd_Unstarted(); it != itEnd; ++it) {
			(*it)->OnAwake();
		}
	}

	template<GameLoopObject T>
	bool GameLoopObjectContainer<T>::OnStartUnstarted()
	{
		bool hasUnstarted = false;

		if constexpr (std::is_same_v<GameObject, T>) {
			for (auto& startedObj : objects_Started) {
				hasUnstarted |= startedObj->OnStartUnstarted();
			}
		}

		if (objects_Unstarted.size() > 0) {
			auto it = objects_Started.insert(
				objects_Started.end(),
				std::make_move_iterator(objects_Unstarted.begin()),
				std::make_move_iterator(objects_Unstarted.end()));

			objects_Unstarted.clear();

			for (; it != objects_Started.end(); ++it) {
				(*it)->OnStart();
			}

			hasUnstarted = true;
		}

		return hasUnstarted;
	}

	template<GameLoopObject T>
	void GameLoopObjectContainer<T>::OnUpdate()
	{
		for (auto it = SimpleBegin_Started(), itEnd = SimpleEnd_Started(); it != itEnd; ++it) {
			(*it)->OnUpdate();
		}
	}

	template<GameLoopObject T>
	void GameLoopObjectContainer<T>::OnLateUpdate()
	{
		for (auto it = SimpleBegin_Started(), itEnd = SimpleEnd_Started(); it != itEnd; ++it) {
			(*it)->OnLateUpdate();
		}
	}

	template<GameLoopObject T>
	void GameLoopObjectContainer<T>::OnPreDestroy()
	{
		for (auto it = SimpleBegin(), itEnd = SimpleEnd(); it != itEnd; ++it) {
			(*it)->OnPreDestroy();
		}
	}

#pragma endregion

#pragma region deprecated

	/*

	template<GameLoopObject T>
	void GameLoopObjectContainer<T>::Transfer(const T& object, GameLoopObjectContainer& from, GameLoopObjectContainer& to)
	{
		if (&from == &to) {
			return;
		}

		std::pair<	std::vector<std::unique_ptr<T>>*,
					std::vector<std::unique_ptr<T>>*>
			pairLists[] = {
			{ &from.objects_Started, &to.objects_Started },
			{ &from.objects_Unstarted, &to.objects_Unstarted },
		};

		for (auto&& [from, to] : pairLists) {
			auto target = std::find_if(
				from->begin(),
				from->end(),
				[&object](const auto& contained) { return *contained == object; });

			if (target != from->end()) {
				to->emplace_back(std::move(*target));
				from->erase(target);
				return;
			}
		}

		DEBUG_LOG_WARNING("GameLoopObjectContainer::Transfer失敗：fromからobjectが見つけられない。");
	}

	*/

#pragma endregion
}

