#include <Beryllium/Platforms/Windows/WindowsWindow.hpp>
#include <Beryllium/Logger.hpp>

#include <Beryllium/Events/CommonEvents.hpp>
#include <Beryllium/Platforms/OpenGL/OpenGLContext.hpp>

#include <imgui.h>

#include <stdexcept>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Beryllium
{
	WindowsWindow::WindowsWindow(const std::string& _title, unsigned int _width, unsigned int _height)
		: Beryllium::Window(_title, _width, _height)
	{
		::WNDCLASSEXA wcex;
		::RECT clientRect;
		::PIXELFORMATDESCRIPTOR pfd;
		int pixelFormat;

		::ZeroMemory(&wcex, sizeof(wcex));
		::ZeroMemory(&pfd, sizeof(pfd));

		wcex.cbSize = sizeof(wcex);
		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wcex.lpfnWndProc = WindowsWindow::WndProc;
		wcex.hInstance = ::GetModuleHandleA(nullptr);
		wcex.hIcon = ::LoadIconA(nullptr, (::LPCSTR)IDI_APPLICATION);
		wcex.hCursor = ::LoadCursorA(nullptr, (::LPCSTR)IDC_ARROW);
		wcex.hbrBackground = (::HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszClassName = BE_WINDOW_CLASS_NAME;
		wcex.hIconSm = ::LoadIconA(nullptr, (::LPCSTR)IDI_APPLICATION);
		::RegisterClassExA(&wcex);

		clientRect.left = 0;
		clientRect.top = 0;
		clientRect.right = _width;
		clientRect.bottom = _height;
		::AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

		m_handle = ::CreateWindowExA(
			0,
			BE_WINDOW_CLASS_NAME,
			_title.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			clientRect.right - clientRect.left,
			clientRect.bottom - clientRect.top,
			nullptr,
			nullptr,
			::GetModuleHandleA(nullptr),
			this
		);

		if (m_handle == nullptr)
		{
			::UnregisterClassA(BE_WINDOW_CLASS_NAME, ::GetModuleHandleA(nullptr));
			throw std::runtime_error("Failed to create window");
		}

		m_context = new Beryllium::OpenGLContext(this);

		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;

		::HDC deviceContext = ::GetDC(m_handle);

		pixelFormat = ::ChoosePixelFormat(deviceContext, &pfd);
		if (pixelFormat == 0)
		{
			::ReleaseDC(m_handle, deviceContext);
			::DestroyWindow(m_handle);
			::UnregisterClassA(BE_WINDOW_CLASS_NAME, ::GetModuleHandleA(nullptr));
			BE_CRITICAL("[System][Window] Failed to choose pixel format");
			throw std::runtime_error("Failed to choose pixel format");
		}

		if (!::SetPixelFormat(deviceContext, pixelFormat, &pfd))
		{
			::ReleaseDC(m_handle, deviceContext);
			::DestroyWindow(m_handle);
			::UnregisterClassA(BE_WINDOW_CLASS_NAME, ::GetModuleHandleA(nullptr));
			BE_CRITICAL("[System][Window] Failed to set pixel format");
			throw std::runtime_error("Failed to set pixel format");
		}

		BE_TRACE("[System][Window] Created");

		m_context->Init();

		::ShowWindow(m_handle, SW_SHOW);
		::SetForegroundWindow(m_handle);
		::SetFocus(m_handle);
	}

	WindowsWindow::~WindowsWindow()
	{
		m_context->Destroy();
		delete m_context;

		::DestroyWindow(m_handle);
		::UnregisterClassA(BE_WINDOW_CLASS_NAME, ::GetModuleHandleA(nullptr));

		BE_TRACE("[System][Window] Destroyed");
	}

	void WindowsWindow::SetTitle(std::string _title)
	{
		::SetWindowTextA(m_handle, _title.c_str());
	}

	std::string WindowsWindow::GetTitle() const
	{
		std::string title;

		int txtLen = ::GetWindowTextLengthA(m_handle);
		::PSTR memBuf = (::PSTR)::VirtualAlloc((::LPVOID)NULL, (::DWORD)(txtLen + 1), MEM_COMMIT, PAGE_READWRITE);

		if (memBuf != nullptr) {
			int realLen = ::GetWindowTextA(m_handle, memBuf, txtLen + 1);
			title = std::string(memBuf);
			::VirtualFree((::LPVOID)memBuf, (::DWORD)(txtLen + 1), MEM_COMMIT);
		}

		return title;
	}

	void WindowsWindow::OnUpdate()
	{
		::MSG msg;
		::ZeroMemory(&msg, sizeof(msg));
		while (::PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessageA(&msg);
		}

		//swap buffers
		m_context->SwapBuffers();
	}

	bool WindowsWindow::IsOpen() const
	{
		return ::IsWindow(m_handle) && IsWindowVisible(m_handle);
	}

	void WindowsWindow::Close()
	{
		::CloseWindow(m_handle);
		::ShowWindow(m_handle, SW_HIDE);

		BE_TRACE("[System][Window] Closed");
	}

	void* WindowsWindow::GetNativeWindow() const
	{
		return m_handle;
	}

	std::pair<float, float> WindowsWindow::GetSize() const
	{
		::RECT rect;
		::GetClientRect(m_handle, &rect);

		return std::make_pair(rect.right - rect.left, rect.bottom - rect.top);
	}

	::LRESULT WindowsWindow::WndProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
	{
		Window* wd = nullptr;

		if (ImGui_ImplWin32_WndProcHandler(_hwnd, _msg, _wParam, _lParam))
		{
			return true;
		}

		if (_msg == WM_NCCREATE)
		{
			::LPCREATESTRUCTA lpcs = (::LPCREATESTRUCTA)_lParam;
			wd = (Window*)lpcs->lpCreateParams;
			::SetWindowLongPtrA(_hwnd, GWLP_USERDATA, (::LONG_PTR)wd);
		}
		else
		{
			wd = (Window*)::GetWindowLongPtrA(_hwnd, GWLP_USERDATA);
			if (wd == nullptr)
			{
				return ::DefWindowProcA(_hwnd, _msg, _wParam, _lParam);
			}
		}


		//::POINTS mp = MAKEPOINTS(_lParam);
		//auto offset = GET_WHEEL_DELTA_WPARAM(_wParam);
		//return (::LRESULT)!wd->eventCallback(MouseButtonReleasedEvent(2, loc.x, loc.y));

		switch (_msg)
		{
			//TODO: mouse events
		case WM_MOUSEMOVE:
		{
			::POINTS mp = MAKEPOINTS(_lParam);
			return (::LRESULT)!wd->DispatchEvent(Events::MouseMoved(mp.x, mp.y));
			break;
		}
		case WM_MOUSEWHEEL:
		{
			::POINTS mp = MAKEPOINTS(_lParam);
			auto offset = GET_WHEEL_DELTA_WPARAM(_wParam);
			return (::LRESULT)!wd->DispatchEvent(Events::MouseScrolled(offset, mp.x, mp.y));
			break;
		}
		case WM_LBUTTONDOWN:
		{
			POINTS loc = MAKEPOINTS(_lParam);
			return (::LRESULT)!wd->DispatchEvent(Events::MouseButtonPressed(Mouse::Button::Left, loc.x, loc.y));
		}
		case WM_MBUTTONDOWN:
		{
			POINTS loc = MAKEPOINTS(_lParam);
			return (::LRESULT)!wd->DispatchEvent(Events::MouseButtonPressed(Mouse::Button::Middle, loc.x, loc.y));
		}
		case WM_RBUTTONDOWN:
		{
			POINTS loc = MAKEPOINTS(_lParam);
			return (::LRESULT)!wd->DispatchEvent(Events::MouseButtonPressed(Mouse::Button::Right, loc.x, loc.y));
		}
		case WM_LBUTTONUP:
		{
			POINTS loc = MAKEPOINTS(_lParam);
			return (::LRESULT)!wd->DispatchEvent(Events::MouseButtonReleased(Mouse::Button::Left, loc.x, loc.y));
		}
		case WM_MBUTTONUP:
		{
			POINTS loc = MAKEPOINTS(_lParam);
			return (::LRESULT)!wd->DispatchEvent(Events::MouseButtonReleased(Mouse::Button::Middle, loc.x, loc.y));
		}
		case WM_RBUTTONUP:
		{
			POINTS loc = MAKEPOINTS(_lParam);
			return (::LRESULT)!wd->DispatchEvent(Events::MouseButtonReleased(Mouse::Button::Right, loc.x, loc.y));
		}
		case WM_LBUTTONDBLCLK:
		{
			POINTS loc = MAKEPOINTS(_lParam);
			return (::LRESULT)!wd->DispatchEvent(Events::MouseButtonPressed(Mouse::Button::Left, loc.x, loc.y, true));
		}
		case WM_MBUTTONDBLCLK:
		{
			POINTS loc = MAKEPOINTS(_lParam);
			return (::LRESULT)!wd->DispatchEvent(Events::MouseButtonPressed(Mouse::Button::Middle, loc.x, loc.y, true));
		}
		case WM_RBUTTONDBLCLK:
		{
			POINTS loc = MAKEPOINTS(_lParam);
			return (::LRESULT)!wd->DispatchEvent(Events::MouseButtonPressed(Mouse::Button::Right, loc.x, loc.y, true));
		}
		case WM_KEYDOWN:
		{
			//if key was already down, ignore
			if (_lParam & 0x40000000)
			{
				break;
			}
			return (::LRESULT)!wd->DispatchEvent(Events::KeyPressed(_wParam));
			break;
		}
		case WM_KEYUP:
		{
			return (::LRESULT)!wd->DispatchEvent(Events::KeyReleased(_wParam));
			break;
		}
		case WM_SIZE:
		{
			//get size
			::RECT rect;
			::GetClientRect(_hwnd, &rect);

			//using GetClientRect, top left corner of client area is (0,0) so just forward the right and bottom values
			return (::LRESULT)!wd->DispatchEvent(Events::WindowResized(rect.right, rect.bottom));
			break;
		}
		case WM_CLOSE:
		{
			return (::LRESULT)!wd->DispatchEvent(Events::WindowClosed());
			break;
		}
		case WM_SETFOCUS:
		{
			return (::LRESULT)!wd->DispatchEvent(Events::WindowFocusChanged(true));
			break;
		}
		case WM_KILLFOCUS:
		{
			return (::LRESULT)!wd->DispatchEvent(Events::WindowFocusChanged(false));
			break;
		}
		case WM_MOVE:
		{
			::POINTS mp = MAKEPOINTS(_lParam);
			return (::LRESULT)!wd->DispatchEvent(Events::WindowMoved(mp.x, mp.y));
			break;
		}

		default:
			return ::DefWindowProcA(_hwnd, _msg, _wParam, _lParam);
		}
		return 0;

	}
}
