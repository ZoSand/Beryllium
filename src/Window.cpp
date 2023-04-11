#include <Beryllium/Window.hpp>

namespace Beryllium
{
	Window::Window(const std::string& _title, unsigned int _width, unsigned int _height)
		: m_data({ _title, _width, _height, this })
	{
	}

	void Window::SetTitle(std::string _title)
	{
		m_data.title = _title;
	}
}