/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *********************************************************************************************/

#include <Beryllium/Windows/Window.hpp>
#include <Beryllium/Common/Application.hpp>

#include <windows.h>

//use for UNICODE definition independence
#define BE_MAKE_ATOM(i) (LPSTR) ((ULONG_PTR)((WORD)(i)))
#define BE_CLASS_NAME "Beryllium_Class"

namespace Be::Platform {
    Window::Window() noexcept
            : Contracts::Window(), m_hwnd(nullptr), m_classAtom(0), m_instance(nullptr) {
    };

    Window::~Window() {
        Platform::Window::Destroy();
    }

    void Window::Create() {
        WNDCLASSEXA wcx;
        ZeroMemory(&wcx, sizeof(WNDCLASSEXA));

        m_instance = GetModuleHandleA(nullptr);

        wcx.cbSize = sizeof(WNDCLASSEXA);
        wcx.lpszClassName = BE_CLASS_NAME;
        wcx.lpfnWndProc = Window::WndProc;
        wcx.hInstance = m_instance;
        wcx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

        m_classAtom = RegisterClassExA(&wcx);

        if (m_classAtom == 0) {
            throw;
        }

        m_hwnd = CreateWindowExA(
                0L,
                BE_MAKE_ATOM(m_classAtom),
                Application::GetApplicationDefaultName().c_str(),
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                nullptr,
                nullptr,
                m_instance,
                this
        );

        if (m_hwnd == nullptr) {
            throw;
        }
    }

    void Window::Destroy() {
        if (m_hwnd != nullptr) {
            DestroyWindow(m_hwnd);
            m_hwnd = nullptr;
        }

        if (m_classAtom != 0) {
            UnregisterClassA(BE_MAKE_ATOM(m_classAtom), m_instance);
            m_classAtom = 0;
        }
    }

    void Window::Update() {
        MSG msg = {};
        while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
    }

    void Window::SetTitle(const std::string &_title) {
        SetWindowTextA(m_hwnd, _title.c_str());
    }

    std::string Window::GetTitle() const {
        int txtLen = GetWindowTextLengthA(m_hwnd) + 1;
        auto wndTxtBuf = new CHAR[txtLen];
        GetWindowTextA(m_hwnd, wndTxtBuf, txtLen);

        std::string title(wndTxtBuf);

        delete[] wndTxtBuf;
        return title;
    }

    void Window::Open(bool _open) {
        ShowWindow(m_hwnd, _open ? SW_SHOW : SW_HIDE);
    }

    bool Window::IsOpen() const {
        return IsWindow(m_hwnd);
    }

    void Window::SetSize(std::pair<int, int> _size) {
        if (m_hwnd != nullptr)
        {
            SetWindowPos(m_hwnd, HWND_TOP, 0, 0, _size.first, _size.second, SWP_NOMOVE | SWP_NOZORDER);
        }
    }

    std::pair<int, int> Window::GetSize() const {
        std::pair<int, int> size;

        if (m_hwnd != nullptr) {
            RECT rect;
            GetWindowRect(m_hwnd, &rect);
            size.first = rect.right - rect.left;
            size.second = rect.bottom - rect.top;
        }

        return size;
    }

    void Window::SetPosition(std::pair<int, int> _position) {
        if (m_hwnd != nullptr) {
            SetWindowPos(m_hwnd, HWND_TOP, _position.first, _position.second, 0, 0, SWP_NOSIZE);
        }
    }

    std::pair<int, int> Window::GetPosition() const {
        std::pair<int, int> position;

        if (m_hwnd != nullptr) {
            POINT windowPosition = { 0, 0 };
            ClientToScreen(m_hwnd, &windowPosition);
            position.first = windowPosition.x;
            position.second = windowPosition.y;
        }

        return position;
    }

    LRESULT CALLBACK Window::WndProc(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam) {
        Window *pWnd;

        if (_uMsg == WM_CREATE) {
            auto createStruct = reinterpret_cast<LPCREATESTRUCTA>(_lParam);
            pWnd = static_cast<Window *>(createStruct->lpCreateParams);
            SetWindowLongPtrA(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        } else {
            pWnd = reinterpret_cast<Window *>(GetWindowLongPtrA(_hwnd, GWLP_USERDATA));
        }

        if (pWnd != nullptr) {
            switch (_uMsg) {
                case WM_CLOSE:
                    DestroyWindow(_hwnd);
                    break;
                case WM_DESTROY:
                    PostQuitMessage(0);
                    break;
                default:
                    return DefWindowProcA(_hwnd, _uMsg, _wParam, _lParam);
            }
            return 0;
        }

        return DefWindowProcA(_hwnd, _uMsg, _wParam, _lParam);
    }
}