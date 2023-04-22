#ifndef BE_MOUSE_BUTTON_RELEASED_EVENT_HPP
#define BE_MOUSE_BUTTON_RELEASED_EVENT_HPP

#	include <Beryllium/Events/Event.hpp>
#	include <Beryllium/Mouse.hpp>

namespace Beryllium::Events
{
	class BE_API MouseButtonReleased : public Event
	{
	public:
		MouseButtonReleased(Mouse::Button _button, int _x, int _y);

		inline Mouse::Button GetButton() const;

		inline int GetX() const;
		inline int GetY() const;
	private:
		Mouse::Button m_Button;
		int m_X;
		int m_Y;
	};
}

#endif // BE_MOUSE_BUTTON_RELEASED_EVENT_HPP