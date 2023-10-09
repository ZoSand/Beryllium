/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *********************************************************************************************/

#include <Beryllium/Application.hpp>
#include <iostream>

namespace Be {
    Application::Application(const CreateMethods& _methods)
            : m_window(nullptr) {
        m_window = _methods.Window();

        m_window->Create();
        m_window->Open(true);
    }

    Application::~Application() {
        m_window->Destroy();

        delete m_window;
    };

    int Application::Run() {
        while (m_window->IsOpen()) {
            m_window->Update();
        }

        return 0;
    }

    Be::Contracts::Window *Application::GetWindow() const {
        return m_window;
    }
}