#ifndef BE_MOUSE_MOVED_EVENT_HPP
#define BE_MOUSE_MOVED_EVENT_HPP

#	include <Beryllium/API.hpp>

#	include <Beryllium/Events/Event.hpp>

namespace Beryllium::Events
{
	class BE_API MouseMoved : public Event
	{
	public:
		MouseMoved(int _x, int _y);

		int GetX() const;

		int GetY() const;

	private:
		int m_x;
		int m_y;
	};
}

#endif // BE_MOUSE_MOVED_EVENT_HPP