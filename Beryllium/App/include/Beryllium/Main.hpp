/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *                         										                             *
 * [Header]                                                                                  *
 * This file defines the entry point and Application creator.                                *
 *********************************************************************************************/

#ifndef BERYLLIUM_APP_MAIN_HPP
#define BERYLLIUM_APP_MAIN_HPP

#   include <Beryllium/Application.hpp>
#   include <Beryllium/Window.hpp>

#   include <vector>
#   include <string>

extern Be::Application* CreateApplication();

int main(int _argc, char* _argv[]);

#define BE_SETUP_METHODS(methods)                                                           \
methods.Window = [](){ return new Be::Implementation::Window(); };

#   define BE_USE_APPLICATION(ClassName, ...)                                               \
		Be::Application* CreateApplication()                                                \
		{                                                                                   \
			__VA_ARGS__                                                                     \
            Be::Application::CreateMethods methods;                                         \
            BE_SETUP_METHODS(methods)                                                       \
			return new ClassName(methods);                                                  \
		}

#endif //BERYLLIUM_APP_MAIN_HPP
