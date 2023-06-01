#ifndef BE_WINDOW_HPP
#define BE_WINDOW_HPP

#	include <Beryllium/API.hpp>

#	include <functional>
#	include <string>
#	include <Beryllium/Events/Event.hpp>
#	include <Beryllium/Events/EventDispatcher.hpp>

namespace Beryllium
{
	class BE_API Window : public EventDispatcher
	{
	public:
		Window(const std::string& _title, std::pair<float, float> _size);
		virtual ~Window() = default;

		Window(const Window&) = delete;
		Window(const Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(const Window&&) = delete;

		virtual void SetTitle(std::string _title) = 0;
		virtual std::string GetTitle() const = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual std::pair<float, float> GetSize() const = 0;

		virtual void OnUpdate() = 0;
		virtual bool IsOpen() const = 0;
		virtual void Close() = 0;
	};
}

#endif