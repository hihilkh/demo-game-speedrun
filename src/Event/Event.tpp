#pragma once
#include <vector>
#include <functional>
#include "Utils/Log.h"

template<class OwnedClass, class... Args>
class Event {
	friend OwnedClass;

public:
	~Event() {}

private:
	//typedef void (*Listener)(Args...);
	typedef std::function<void(Args...)> Listener;

	std::vector<Listener*> listeners;

	void Invoke(Args... args) const {
		for (Listener* pListener : listeners) {
			try {
				(*pListener)(args...);
			}
			catch (const std::exception& ex) {
				PrintWarning(ex.what());
			}
			catch (...) {
				PrintWarning("•s–¾‚ÈƒGƒ‰[");
			}
		}
	}

public:
	void AddListener(Listener& listener) {
		listeners.push_back(&listener);
	}

	void RemoveListener(Listener& listener) {
		auto target = std::find(listeners.begin(), listeners.end(), &listener);
		if (target != listeners.end()) {
			listeners.erase(target);
		}
	}
};