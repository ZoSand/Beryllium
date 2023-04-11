#ifndef BE_EVENT_LISTENER_HPP
#define BE_EVENT_LISTENER_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Events/Event.hpp>

#	include <functional>
#	include <vector>

namespace Beryllium {
	class BE_API EventListener
	{
	public:
		EventListener() = default;
		virtual ~EventListener() = default;

		EventListener(const EventListener&) = delete;
		EventListener(const EventListener&&) = delete;
		EventListener& operator=(const EventListener&) = delete;
		EventListener& operator=(const EventListener&&) = delete;

		virtual bool OnEvent(Event& _event) = 0;
	};
}

#endif // BE_EVENT_LISTENER_HPP