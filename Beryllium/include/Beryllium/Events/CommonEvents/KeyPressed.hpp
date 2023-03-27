#ifndef BE_KEY_PRESSSED_EVENT_HPP
#define BE_KEY_PRESSSED_EVENT_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Events/Event.hpp>

namespace Beryllium::Events
{
	class BE_API KeyPressed : public Event
	{
	public:
		KeyPressed(int _key);

		int GetKey() const;

	private:
		int m_key;
	};
}

#endif // BE_KEY_PRESSSED_EVENT_HPP