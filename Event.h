#pragma once

#include<vector>
#include <functional>
#include<string>

using namespace std;

template<typename... Args>
class Event
{
	//list of funtion pointers
	vector<void (*)(Args...)>* callbacks;
public:
	//initializes callbacks on heap
	Event();
	//destroys callbacks vector
	~Event();

	//calls all funtion pointers
	void Invoke(Args... args);

	//add function to callbacks vector
	void AddCallback(void (*newCallback)(Args...));

	//remove funtion from callbacks
	void RemoveCallback(void (*removeCallback)(Args...));

	//remove all callbacks
	void ClearCallbacks();

	//overload += and -= to call subscribe/unsubscribe
	void operator+=(void (*newCallback)(Args...));
	void operator-=(void (*newCallback)(Args...));
	void operator()(Args... args);
};

template<typename... Args>
Event<Args...>::Event()
	: callbacks(new vector<void (*)(Args...)>())
{

}

template<typename... Args>
Event<Args...>::~Event()
{
	delete callbacks;
	callbacks = nullptr;
}

template<typename... Args>
void Event<Args...>::Invoke(Args... args)
{
	for (auto callback : *callbacks)
	{
		callback(args...);
	}
}

template<typename... Args>
void Event<Args...>::AddCallback(void (*newCallback)(Args...))
{
	for (auto callback = begin(*callbacks); callback != end(*callbacks); ++callback) {
		if (*callback == newCallback)
		{
			return;
		}
	}

	callbacks->push_back(newCallback);
}

template<typename... Args>
void Event<Args...>::RemoveCallback(void (*removeCallback)(Args...))
{
	for (auto callback = begin(*callbacks); callback != end(*callbacks); ++callback) {
		if (*callback == removeCallback)
		{
			callbacks->erase(callback);
			break;
		}
	}
}

template<typename... Args>
void Event<Args...>::ClearCallbacks()
{
	callbacks->clear();
}

template<typename... Args>
void Event<Args...>::operator+=(void (*newCallback)(Args...))
{
	AddCallback(newCallback);
}

template<typename... Args>
void Event<Args...>::operator-=(void (*removeCallback)(Args...))
{
	RemoveCallback(removeCallback);
}

template<typename... Args>
void Event<Args...>::operator()(Args... args)
{
	Invoke(args...);
}

