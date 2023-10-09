/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *                         										                             *
 * [Header]                                                                                  *
 * This file defines the Beryllium Application interface.                                    *
 *********************************************************************************************/

#ifndef BERYLLIUM_APPLICATION_HPP
#define BERYLLIUM_APPLICATION_HPP

#   include <Beryllium/CoreApi.hpp>

#   include <Beryllium/Contracts/Window.hpp>

#   include <functional>

namespace Be {
    class BE_CORE_API_PUBLIC Application {
    public:
        struct CreateMethods {
            std::function<Contracts::Window*()> Window;
        };

    public:
        [[maybe_unused]]
        explicit Application(const CreateMethods& _methods);

        virtual ~Application();

        [[maybe_unused, nodiscard]]
        int Run();

        [[nodiscard]]
        Be::Contracts::Window *GetWindow() const;

    private:
        Be::Contracts::Window *m_window;
    };
}

#endif //BERYLLIUM_APPLICATION_HPP
