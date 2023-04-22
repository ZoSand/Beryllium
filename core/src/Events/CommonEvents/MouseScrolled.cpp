#include <Beryllium/Events/CommonEvents/MouseScrolled.hpp>

namespace Beryllium::Events
{
	MouseScrolled::MouseScrolled(int _offset, int _x, int _y)
		: m_offset(_offset), m_x(_x), m_y(_y)
	{
	}

	int MouseScrolled::GetOffset() const
	{
		return m_offset;
	}

	int MouseScrolled::GetX() const
	{
		return m_x;
	}

	int MouseScrolled::GetY() const
	{
		return m_y;
	}
}
