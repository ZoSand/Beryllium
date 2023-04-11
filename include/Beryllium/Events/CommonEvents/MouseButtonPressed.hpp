#ifndef BE_MOUSE_BUTTON_PRESSED_EVENT_HPP
#define BE_MOUSE_BUTTON_PRESSED_EVENT_HPP

#	include <Beryllium/Events/Event.hpp>
#	include <Beryllium/Mouse.hpp>

namespace Beryllium::Events
{
	class BE_API MouseButtonPressed : public Event
	{
	public:
		MouseButtonPressed(Mouse::Button _button, int _x, int _y, bool _dblClk = false);

		inline Mouse::Button GetButton() const;
		inline bool IsDoubleClick() const;

		inline int GetX() const;
		inline int GetY() const;
	private:
		Mouse::Button m_Button;
		bool m_DoubleClick;
		int m_X;
		int m_Y;
	};
}

#endif // BE_MOUSE_BUTTON_PRESSED_EVENT_HPP