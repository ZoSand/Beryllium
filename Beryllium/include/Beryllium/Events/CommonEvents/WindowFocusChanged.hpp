#ifndef BE_WINDOW_FOCUS_CHANGED_HPP
#define BE_WINDOW_FOCUS_CHANGED_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Events/Event.hpp>

namespace Beryllium::Events
{
	class BE_API WindowFocusChanged : public Event
	{
	public:
		WindowFocusChanged(bool _focused);

		bool IsFocused() const;

	private:
		bool m_focused;
	};
}

#endif // BE_WINDOW_FOCUS_CHANGED_HPP