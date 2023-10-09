/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *                         										                             *
 * [Header]                                                                                  *
 * This file implements the Window class contract for X11 platforms.                         *
 *********************************************************************************************/

#ifndef BERYLLIUM_IMPLEMENTATION_X11_WINDOW_HPP
#define BERYLLIUM_IMPLEMENTATION_X11_WINDOW_HPP

#   include <Beryllium/PlatformApi.hpp>

#   include <Beryllium/Contracts/Window.hpp>

#   include <X11/Xlib.h>

namespace Be::Implementation
{
class BE_PLATFORM_API_PUBLIC Window : public Be::Contracts::Window {
    public:        Window() noexcept;

    ~Window() override;

    [[maybe_unused]]
    void Create() override;
    [[maybe_unused]]
    void Destroy() override;
    [[maybe_unused]]
    void Update() override;

    [[maybe_unused]]
    void SetTitle(const std::string &_title) override;
    [[maybe_unused, nodiscard]]
    std::string GetTitle() const override;

    [[maybe_unused]]
    void Open(bool _open) override;
    [[maybe_unused, nodiscard]]
    bool IsOpen() const override;

    [[maybe_unused]]
    void SetSize(std::pair<int, int> _size) override;
    [[maybe_unused, nodiscard]]
    std::pair<int, int> GetSize() const override;

    [[maybe_unused]]
    void SetPosition(std::pair<int, int> _position) override;
    [[maybe_unused, nodiscard]]
    std::pair<int, int> GetPosition() const override;

    protected:
    [[maybe_unused, nodiscard]]
    std::string GetApplicationDefaultTitle() override;

    private:
        Display* m_display;
        ::Window m_window;
        Screen* m_screen;
        Atom m_atomWmDeleteMessage;

        bool m_init;
        bool m_shouldClose;
    };
}

#endif //BERYLLIUM_IMPLEMENTATION_X11_WINDOW_HPP
