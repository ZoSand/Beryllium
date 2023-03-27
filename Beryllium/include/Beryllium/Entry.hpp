#ifndef BE_ENTRY_HPP
#define BE_ENTRY_HPP

#	include <Beryllium/Application.hpp>
#	include <locale>

extern Beryllium::Application* Beryllium::CreateApplication(Beryllium::CmdArgs _args);

#	if defined(BE_PLATFORM_WINDOWS)
#		define BE_ENTRY															\
			int main(int _argc, char* _argv[])									\
			{																	\
				std::setlocale(LC_ALL, "");										\
				auto app = Beryllium::CreateApplication( { _argc, _argv } );	\
				app->Run();														\
				delete app;														\
			}
#	endif

#	define BE_ENTRY_APP(appName, appClass)												\
		Beryllium::Application* Beryllium::CreateApplication(Beryllium::CmdArgs _args)	\
		{																				\
			Beryllium::ApplicationSpecs specs;											\
			specs.name = appName;														\
			specs.args = _args;															\
			return new appClass(specs);													\
		}																				\
		BE_ENTRY

#endif // BE_ENTRY_HPP