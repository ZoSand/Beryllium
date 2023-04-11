#ifndef BE_MOUSE_SCROLLED_EVENT_HPP
#define BE_MOUSE_SCROLLED_EVENT_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Events/Event.hpp>

namespace Beryllium::Events
{
	class BE_API MouseScrolled : public Event
	{
	public:
		MouseScrolled(int _offset, int _x, int _y);

		int GetOffset() const;

		int GetX() const;

		int GetY() const;

	private:
		int m_offset;
		int m_x;
		int m_y;
	};
}

#endif // BE_MOUSE_SCROLLED_EVENT_HPP