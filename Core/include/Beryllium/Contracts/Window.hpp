/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *                         										                             *
 * [Header]                                                                                  *
 * This file describe the Window class contract.                                             *
 *********************************************************************************************/

#ifndef BERYLLIUM_CORE_CONTRACTS_WINDOW_HPP
#define BERYLLIUM_CORE_CONTRACTS_WINDOW_HPP

#   include <string>
#   include <utility>

namespace Be::Contracts
{
    class Window
    {
    public:
        Window() = default;

        virtual ~Window() = default;

        [[maybe_unused]]
        virtual void Create() = 0;
        [[maybe_unused]]
        virtual void Destroy() = 0;
        [[maybe_unused]]
        virtual void Update() = 0;

        [[maybe_unused]]
        virtual void SetTitle(const std::string &_title) = 0;
        [[maybe_unused, nodiscard]]
        virtual std::string GetTitle() const = 0;

        [[maybe_unused]]
        virtual void Open(bool _open) = 0;
        [[maybe_unused, nodiscard]]
        virtual bool IsOpen() const = 0;

        [[maybe_unused]]
        virtual void SetSize(std::pair<int, int> _size) = 0;
        [[maybe_unused, nodiscard]]
        virtual std::pair<int, int> GetSize() const = 0;

        [[maybe_unused]]
        virtual void SetPosition(std::pair<int, int> _position) = 0;
        [[maybe_unused, nodiscard]]
        virtual std::pair<int, int> GetPosition() const = 0;

    protected:
        [[maybe_unused, nodiscard]]
        virtual std::string GetApplicationDefaultTitle() = 0;
    };
}


#endif //BERYLLIUM_CORE_CONTRACTS_WINDOW_HPP
