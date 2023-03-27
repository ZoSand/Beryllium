#ifndef BE_KEY_RELEASED_EVENT_HPP
#define BE_KEY_RELEASED_EVENT_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Events/Event.hpp>

namespace Beryllium::Events
{
	class BE_API KeyReleased : public Event
	{
	public:
		KeyReleased(int _key);

		int GetKey() const;

	private:
		int m_key;
	};
}

#endif // BE_KEY_RELEASED_EVENT_HPP