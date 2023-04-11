#ifndef BE_WINDOW_CLOSED_EVENT_HPP
#define BE_WINDOW_CLOSED_EVENT_HPP

#include <Beryllium/API.hpp>
#include <Beryllium/Events/Event.hpp>

namespace Beryllium::Events
{
	class BE_API WindowClosed : public Event
	{
	public:
		WindowClosed();
	};
}

#endif // BE_WINDOW_CLOSED_EVENT_HPP