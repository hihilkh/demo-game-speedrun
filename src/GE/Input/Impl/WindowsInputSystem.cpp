#include "GE/Utils/PreprocessorDef.h"

#if _INPUT == INPUT_WINDOWS

#include "../InputSystem.h"
#include <unordered_set>
#include <vector>
#include <algorithm>

// TODO : ロック？
namespace GE::Input
{
	namespace
	{
		std::unordered_set<KeyCode> keyDownSet;
		std::unordered_set<KeyCode> keyDownSet2;
		std::unordered_set<KeyCode> keyUpSet;
		std::unordered_set<KeyCode> keyUpSet2;

		std::unordered_set<KeyCode>* pCurrentKeyDownSet = &keyDownSet;
		std::unordered_set<KeyCode>* pCacheKeyDownSet = &keyDownSet2;
		std::unordered_set<KeyCode>* pCurrentKeyUpSet = &keyUpSet;
		std::unordered_set<KeyCode>* pCacheKeyUpSet = &keyUpSet2;

		std::unordered_set<KeyCode> keyOnSet;
		std::unordered_set<KeyCode> keyOnWaitForAddSet;
		std::unordered_set<KeyCode> keyOnWaitForRemoveSet;
	}

	bool GetKeyDown(KeyCode keyCode)
	{
		return pCurrentKeyDownSet->find(keyCode) != pCurrentKeyDownSet->end();
	}

	bool GetKeyUp(KeyCode keyCode)
	{
		return pCurrentKeyUpSet->find(keyCode) != pCurrentKeyUpSet->end();
	}

	bool GetKeyOn(KeyCode keyCode)
	{
		return keyOnSet.find(keyCode) != keyOnSet.end();
	}

	void InputSystem::OnUpdate()
	{
		pCurrentKeyDownSet->clear();
		std::swap(pCurrentKeyDownSet, pCacheKeyDownSet);

		pCurrentKeyUpSet->clear();
		std::swap(pCurrentKeyUpSet, pCacheKeyUpSet);

		if (keyOnWaitForAddSet.size() > 0) {
			keyOnSet.insert(keyOnWaitForAddSet.cbegin(), keyOnWaitForAddSet.cend());
			keyOnWaitForAddSet.clear();
		}

		for (auto keyCode : keyOnWaitForRemoveSet) {
			keyOnSet.erase(keyCode);
		}
		keyOnWaitForRemoveSet.clear();
	}

	namespace Internal
	{
		void OnKeyDown(KeyCode keyCode)
		{
			if (GetKeyOn(keyCode)) {
				size_t count = keyOnWaitForRemoveSet.erase(keyCode);

				// 1フレームの中で同じkeyCodeのOnKeyUpを呼び出してから、OnKeyDownを呼び出す場合
				if (count > 0) {
					pCacheKeyDownSet->insert(keyCode);
				}
				return;
			}

			keyOnWaitForAddSet.insert(keyCode);
			pCacheKeyDownSet->insert(keyCode);
		}

		void OnKeyUp(KeyCode keyCode)
		{
			if (!GetKeyOn(keyCode)) {
				size_t count = keyOnWaitForAddSet.erase(keyCode);

				// 1フレームの中で同じkeyCodeのOnKeyDownを呼び出してから、OnKeyUpを呼び出す場合
				if (count > 0) {
					pCacheKeyUpSet->insert(keyCode);
				}
				return;
			}

			keyOnWaitForRemoveSet.insert(keyCode);
			pCacheKeyUpSet->insert(keyCode);
		}
	}
}


#endif