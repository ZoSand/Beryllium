#include <Beryllium/Events/CommonEvents/MouseButtonPressed.hpp>

namespace Beryllium::Events
{
	MouseButtonPressed::MouseButtonPressed(Mouse::Button _button, int _x, int _y, bool _dblClk)
		: m_Button(_button)
		, m_DoubleClick(_dblClk)
		, m_X(_x)
		, m_Y(_y)
	{
	}

	int MouseButtonPressed::GetX() const
	{
		return m_X;
	}

	int MouseButtonPressed::GetY() const
	{
		return m_Y;
	}

	Mouse::Button MouseButtonPressed::GetButton() const
	{
		return m_Button;
	}

	bool MouseButtonPressed::IsDoubleClick() const
	{
		return m_DoubleClick;
	}
}