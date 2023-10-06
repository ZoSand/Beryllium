/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *********************************************************************************************/

#include <Beryllium/Common/Application.hpp>
#include <iostream>


#if defined(BERYLLIUM_PLATFORM_WINDOWS)
#   include <shlwapi.h>
#elif defined(BERYLLIUM_PLATFORM_LINUX)
#   include <unistd.h>
#   include <libgen.h>
#   include <cstring>

#endif

namespace Be {
    Application::Application(const std::vector<std::string> &_arguments)
            : m_window(nullptr) {
        (void) _arguments;
        m_window = new Window();

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

    Platform::Window *Application::GetWindow() const {
        return m_window;
    }

    std::string Application::GetApplicationDefaultName() {
        std::string defaultName;
#if defined(BERYLLIUM_PLATFORM_WINDOWS)
        char buffer[MAX_PATH];
        if (GetModuleFileNameA(nullptr, buffer, MAX_PATH) != 0) {
            PathStripPathA(buffer);
            PathRemoveExtensionA(buffer);
            defaultName = buffer;
        }
#elif defined(BERYLLIUM_PLATFORM_LINUX)
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
#endif
        return defaultName;
    }
}