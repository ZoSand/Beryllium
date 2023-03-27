#include "Application.hpp"

namespace Sangenpai
{
	Application::Application(Beryllium::ApplicationSpecs _specs)
		: Beryllium::Application(_specs)
	{
		Beryllium::Logger::Info("Hello Sangenpai!");
	}

	Application::~Application()
	{
		Beryllium::Logger::Info("Goodbye Sangenpai!");
	}
}