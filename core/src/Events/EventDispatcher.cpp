#include <Beryllium/Events/EventDispatcher.hpp>

namespace Beryllium
{
	bool EventDispatcher::DispatchEvent(Event& _event)
	{
		for (auto& listener : m_listeners)
		{
			if (listener->OnEvent(_event))
			{
				return true;
			}
		}
		return false;
	}

	void EventDispatcher::AddListener(EventListener* _listener)
	{
		m_listeners.push_back(_listener);
	}

	void EventDispatcher::RemoveListener(EventListener* _listener)
	{
		m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), _listener), m_listeners.end());
	}

	size_t EventDispatcher::GetListenerCount() const
	{
		return m_listeners.size();
	}
}