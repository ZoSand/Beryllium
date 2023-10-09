/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *********************************************************************************************/

#include <Beryllium/Window.hpp>

#include <unistd.h>
#include <libgen.h>
#include <cstring>

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
        SetTitle(Application::GetApplicationDefaultName());
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
        if (m_display == nullptr || m_window == None){
            return;
        }
        XStoreName(m_display, m_window, _title.c_str());
        XFlush(m_display);
    }

    std::string Window::GetTitle() const {
        std::string title;
        char* windowName = nullptr;
        if (m_display == nullptr || m_window == None){
            return title;
        }
        XFetchName(m_display, m_window, &windowName);
        if (windowName != nullptr)
        {
            title = windowName;
            XFree(windowName);
        }
        return title;
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
        if (m_display == nullptr || m_window == None){
            return;
        }
        XResizeWindow(m_display, m_window, _size.first, _size.second);
        XFlush(m_display);
    }

    std::pair<int, int> Window::GetSize() const {
        std::pair<int, int> size;
        if (m_display == nullptr || m_window == None){
            return size;
        }
        XWindowAttributes wndAttribs;
        XGetWindowAttributes(m_display, m_window, &wndAttribs);
        size = std::make_pair(wndAttribs.width, wndAttribs.height);
        return size;
    }

    void Window::SetPosition(std::pair<int, int> _position) {
        if (m_display == nullptr || m_window == None) {
            return;
        }
        XMoveWindow(m_display, m_window, _position.first, _position.second);
        XFlush(m_display);
    }

    std::pair<int, int> Window::GetPosition() const {
        std::pair<int, int> position;
        if (m_display == nullptr || m_window == None){
            return position;
        }
        XWindowAttributes wndAttribs;
        XGetWindowAttributes(m_display, m_window, &wndAttribs);
        position = std::make_pair(wndAttribs.x, wndAttribs.y);
        return position;
    }

    std::string Window::GetApplicationDefaultTitle() {
        std::string defaultName;
        char buffer[4096];
        ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
        if (len != -1) {
            buffer[len] = '\0';
            const char* exeName = basename(buffer);
            char* extPos = const_cast<char*>(strrchr(exeName, '.'));
            if (extPos != nullptr) {
                *extPos = '\0';
            }
            defaultName = exeName;
        }
        return defaultName;
    }
}