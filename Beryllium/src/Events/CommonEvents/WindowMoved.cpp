#include <Beryllium/Events/CommonEvents/WindowMoved.hpp>

namespace Beryllium::Events
{
	WindowMoved::WindowMoved(int _x, int _y)
		: m_x(_x), m_y(_y)
	{
	}

	int WindowMoved::GetX() const
	{
		return m_x;
	}

	int WindowMoved::GetY() const
	{
		return m_y;
	}
}