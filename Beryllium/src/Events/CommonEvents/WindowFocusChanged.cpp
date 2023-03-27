#include <Beryllium/Events/CommonEvents/WindowFocusChanged.hpp>

namespace Beryllium::Events
{
	WindowFocusChanged::WindowFocusChanged(bool _focused)
		: m_focused(_focused)
	{
	}

	bool WindowFocusChanged::IsFocused() const
	{
		return m_focused;
	}
}