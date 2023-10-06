/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *                         										                             *
 * [Header]                                                                                  *
 * This file defines the entry point and Application creator.                                *
 *********************************************************************************************/

#ifndef BERYLLIUM_MAIN_HPP
#define BERYLLIUM_MAIN_HPP

#   include <Beryllium/Common/Application.hpp>

#   include <vector>
#   include <string>

#   define BE_USE_MAIN()                                                                    \
        Be::Application* CreateApplication(const std::vector<std::string>& _arguments);     \
																							\
		int main(int _argc, char* _argv[]) {                                                \
            int returnCode;                                                                 \
            std::vector<std::string> arguments(_argc);                                      \
            for(Be::u32 argId = 0; argId < _argc; argId++)                                  \
			{                                                                               \
                arguments.emplace_back(_argv[argId]);                                       \
			}                                                                               \
                                                                                            \
			Be::Application* app = CreateApplication(arguments);                            \
			returnCode = app->Run();                                                        \
                                                                                            \
			delete app;                                                                     \
			return returnCode;                                                              \
		}

#   define BE_USE_APPLICATION(ClassName, ...)                                               \
		BE_USE_MAIN()                                                                       \
		Be::Application* CreateApplication(const std::vector<std::string>& _arguments)      \
		{                                                                                   \
			__VA_ARGS__                                                                     \
			return new ClassName(_arguments);                                               \
		}                                                                                   \

#endif //BERYLLIUM_MAIN_HPP
