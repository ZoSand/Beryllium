#ifndef BE_ENTRY_HPP
#define BE_ENTRY_HPP

#	include <Beryllium/Application.hpp>
#	include <locale>

extern Beryllium::Application* Beryllium::CreateApplication(Beryllium::CmdArgs _args);

#	if defined(BE_PLATFORM_WINDOWS)
int main(int _argc, char* _argv[])
{
	std::setlocale(LC_ALL, "");
	auto app = Beryllium::CreateApplication({ _argc, _argv });
	app->Run();
	delete app;
}
#	endif

#endif // BE_ENTRY_HPP