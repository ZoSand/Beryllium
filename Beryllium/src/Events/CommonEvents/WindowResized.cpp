#include <Beryllium/Events/CommonEvents/WindowResized.hpp>

namespace Beryllium::Events
{
	WindowResized::WindowResized(unsigned int _width, unsigned int _height)
		: m_width(_width), m_height(_height)
	{
	}

	unsigned int WindowResized::GetWidth() const
	{
		return m_width;
	}

	unsigned int WindowResized::GetHeight() const
	{
		return m_height;
	}
}