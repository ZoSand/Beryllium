#ifndef BE_WINDOWS_WINDOW_HPP
#define BE_WINDOWS_WINDOW_HPP

#	include <Beryllium/Window.hpp>

#	include <Beryllium/Renderer/GraphicsContext.hpp>

#	include <Windows.h>

#	define BE_WINDOW_CLASS_NAME "BerylliumWindowClass"

namespace Beryllium
{
	class BE_API WindowsWindow : public Beryllium::Window
	{
	public:
		WindowsWindow(const std::string& _title, std::pair<float, float> _size);
		virtual ~WindowsWindow();

		virtual void SetTitle(std::string _title) override;
		virtual std::string GetTitle() const override;

		virtual void* GetNativeWindow() const override;

		virtual std::pair<float, float> GetSize() const override;

		virtual void OnUpdate() override;
		virtual bool IsOpen() const override;
		virtual void Close() override;

		void SetVSync(bool _enable) override;

	private:
		::HWND m_handle = nullptr;

		static ::LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
	};
}

#endif