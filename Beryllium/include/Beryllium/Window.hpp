#ifndef BE_WINDOW_HPP
#define BE_WINDOW_HPP

#	include <Beryllium/API.hpp>

#	include <functional>
#	include <string>
#	include <Beryllium/Events/Event.hpp>
#	include <Beryllium/Events/EventDispatcher.hpp>

namespace Beryllium
{
	struct WindowData
	{
		std::string title;
		unsigned int width, height;
		Beryllium::EventDispatcher* dispatcher;
	};

	class BE_API Window : public EventDispatcher
	{
	public:
		Window(const std::string& _title, unsigned int _width, unsigned int _height);
		virtual ~Window() = default;

		Window(const Window&) = delete;
		Window(const Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(const Window&&) = delete;

		virtual void SetTitle(std::string _title);

		virtual void OnUpdate() = 0;
		virtual bool IsOpen() const = 0;
		virtual void Close() = 0;
		virtual void* GetNativeWindow() const = 0;

	protected:
		Beryllium::WindowData m_data;
	};
}

#endif