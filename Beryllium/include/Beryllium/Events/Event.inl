#ifndef BE_EVENT_INL
#define BE_EVENT_INL

#include <Beryllium/Events/Event.hpp>

template <typename T>
const bool Beryllium::Event::Is() const
{
	//events are polymorphic to allow to create custom events for the end user that inherit from Beryllium::Event,
	//so we can use dynamic_cast to check if the event is of the type we want
	return dynamic_cast<const T*>(this) != nullptr;
}

template<typename T>
inline const T& Beryllium::Event::As() const
{
	//cast to T
	return dynamic_cast<const T&>(*this);
}

#endif // BE_EVENT_INL