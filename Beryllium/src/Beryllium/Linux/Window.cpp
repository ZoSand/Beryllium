/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *********************************************************************************************/

#include <Beryllium/Linux/Window.hpp>
#include <Beryllium/Common/Application.hpp>
#include <iostream>

namespace Be::Platform {
    Window::Window() noexcept
            : Contracts::Window(), m_display(nullptr), m_screen(nullptr), m_window(None), m_atomWmDeleteMessage(None), m_init(false), m_shouldClose(false){
    };

    Window::~Window() {
        Platform::Window::Destroy();
    }

    void Window::Create() {
        int screenId;
        m_display = XOpenDisplay(nullptr);
        if (m_display == nullptr) {
            throw;
        }

        m_screen = DefaultScreenOfDisplay(m_display);
        if (m_screen == nullptr) {
            throw;
        }
        screenId = DefaultScreen(m_screen);

        m_window = XCreateSimpleWindow(m_display, RootWindowOfScreen(m_screen), 0, 0, 320, 200, 1, BlackPixel(m_display, screenId),
                                       WhitePixel(m_display, screenId));
        if (m_window == None) {
            throw;
        }

        m_atomWmDeleteMessage = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
        if (m_atomWmDeleteMessage == None)
        {
            throw;
        }

        XSetWMProtocols(m_display, m_window, &m_atomWmDeleteMessage, 1);
    }

    void Window::Destroy() {
        if (m_window != 0) {
            XDestroyWindow(m_display, m_window);
            m_window = 0;
        }

        if (m_screen != nullptr) {
            XFree(m_screen);
            m_screen = nullptr;
        }

        if (m_display != nullptr && *((int*)(m_display)) != 0) {
            XCloseDisplay(m_display);
            m_display = nullptr;
        }
    }

    void Window::Update() {
        XEvent event;

        if (m_display == nullptr)
        {
            return;
        }

        while (XPending(m_display) > 0)
        {
            XNextEvent(m_display, &event);

            switch (event.type) {
                case MapNotify:
                {
                    if (event.xmap.window == m_window) {
                        m_init = true;
                    }
                }
                case ClientMessage:
                {
                    if (event.xclient.data.l[0] == static_cast<long>(m_atomWmDeleteMessage))
                    {
                        m_shouldClose = true;
                    }
                }
            }
        }
    }

    void Window::SetTitle(const std::string &_title) {

    }

    std::string Window::GetTitle() const {
        return std::string{""};
    }

    void Window::Open(bool _open) {
        if (m_display == nullptr || m_window == 0) {
            return;
        }

        if (_open) {
            XMapWindow(m_display, m_window);
        } else {
            XUnmapWindow(m_display, m_window);
        }
    }

    bool Window::IsOpen() const {
        if (m_display == nullptr || m_window == 0) {
            return false;
        }

        XWindowAttributes wndAttributes;
        XGetWindowAttributes(m_display, m_window, &wndAttributes);

        return (wndAttributes.map_state == IsViewable || !m_init) && (!m_shouldClose);
    }

    void Window::SetSize(std::pair<int, int> _size) {

    }

    std::pair<int, int> Window::GetSize() const {
        return std::make_pair<int, int>(0, 0);
    }

    void Window::SetPosition(std::pair<int, int> _position) {

    }

    std::pair<int, int> Window::GetPosition() const {
        return std::make_pair<int, int>(0, 0);
    }
}
