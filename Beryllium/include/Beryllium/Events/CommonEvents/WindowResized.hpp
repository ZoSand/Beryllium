#ifndef BE_WINDOW_RESIZE_EVENT_HPP
#define BE_WINDOW_RESIZE_EVENT_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Events/Event.hpp>

namespace Beryllium::Events
{
	class BE_API WindowResized : public Event
	{
	public:
		WindowResized(unsigned int _width, unsigned int _height);

		unsigned int GetWidth() const;

		unsigned int GetHeight() const;

	private:
		unsigned int m_width;
		unsigned int m_height;
	};
}

#endif // BE_WINDOW_RESIZE_EVENT_HPP