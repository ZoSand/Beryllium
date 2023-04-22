#include <Beryllium/Events/CommonEvents/MouseButtonReleased.hpp>

namespace Beryllium::Events
{
	MouseButtonReleased::MouseButtonReleased(Mouse::Button _button, int _x, int _y)
		: m_Button(_button)
		, m_X(_x)
		, m_Y(_y)
	{
	}

	int MouseButtonReleased::GetX() const
	{
		return m_X;
	}

	int MouseButtonReleased::GetY() const
	{
		return m_Y;
	}

	Mouse::Button MouseButtonReleased::GetButton() const
	{
		return m_Button;
	}
}