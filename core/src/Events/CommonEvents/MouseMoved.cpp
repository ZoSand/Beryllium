#include <Beryllium/Events/CommonEvents/MouseMoved.hpp>


namespace Beryllium::Events
{
	MouseMoved::MouseMoved(int _x, int _y)
		: m_x(_x), m_y(_y)
	{
	}

	int MouseMoved::GetX() const
	{
		return m_x;
	}

	int MouseMoved::GetY() const
	{
		return m_y;
	}
}
