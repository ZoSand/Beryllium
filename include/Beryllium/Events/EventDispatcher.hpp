#ifndef BE_EVENT_EMITTER_HPP
#define BE_EVENT_EMITTER_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Events/Event.hpp>
#	include <Beryllium/Events/EventListener.hpp>

#	include <vector>

namespace Beryllium
{

	class BE_API EventDispatcher
	{
	public:
		EventDispatcher() = default;
		~EventDispatcher() = default;

		EventDispatcher(const EventDispatcher&) = delete;
		EventDispatcher(const EventDispatcher&&) = delete;
		EventDispatcher& operator=(const EventDispatcher&) = delete;
		EventDispatcher& operator=(const EventDispatcher&&) = delete;

		bool DispatchEvent(Event& _event);

		void AddListener(EventListener* _listener);
		void RemoveListener(EventListener* _listener);

		std::size_t GetListenerCount() const;

	private:
		std::vector<EventListener*> m_listeners;
	};
}

#endif // BE_EVENT_EMITTER_HPP