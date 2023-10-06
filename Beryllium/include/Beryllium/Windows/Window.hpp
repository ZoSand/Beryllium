/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *                         										                             *
 * [Header]                                                                                  *
 * This file implements the Window class contract for Win32 platform.                        *
 *********************************************************************************************/

#ifndef BERYLLIUM_IMPLEMENTATION_WIN32_WINDOW_HPP
#define BERYLLIUM_IMPLEMENTATION_WIN32_WINDOW_HPP

#   include <Beryllium/Common/Meta.hpp>
#   include <Beryllium/Common/Api.hpp>

#   include <Beryllium/Contracts/Window.hpp>

#   include <windows.h>

namespace Be::Platform {
    class BE_API_PUBLIC Window : public Contracts::Window {
    public:
        Window() noexcept;

        ~Window() override;

        META_UNUSED_IMPLEMENTATION              (void Create());
        META_UNUSED_IMPLEMENTATION              (void Destroy());
        META_UNUSED_IMPLEMENTATION              (void Update());

        META_UNUSED_IMPLEMENTATION              (void SetTitle(const std::string &_title));
        META_UNUSED_NODISCARD_IMPLEMENTATION    (std::string GetTitle() const);

        META_UNUSED_IMPLEMENTATION              (void Open(bool _open));
        META_UNUSED_NODISCARD_IMPLEMENTATION    (bool IsOpen() const);

        META_UNUSED_IMPLEMENTATION              (void SetSize(std::pair<int, int> _size));
        META_UNUSED_NODISCARD_IMPLEMENTATION    (std::pair<int, int> GetSize() const);

        META_UNUSED_IMPLEMENTATION              (void SetPosition(std::pair<int, int> _position));
        META_UNUSED_NODISCARD_IMPLEMENTATION    (std::pair<int, int> GetPosition() const);

    private:
        HWND m_hwnd;
        ATOM m_classAtom;
        HINSTANCE m_instance;

        static LRESULT CALLBACK WndProc(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);
    };
}

#endif //BERYLLIUM_IMPLEMENTATION_WIN32_WINDOW_HPP
