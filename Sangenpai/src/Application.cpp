#include "Application.hpp"

namespace Sangenpai
{
	Application::Application(Beryllium::ApplicationSpecs _specs)
		: Beryllium::Application(_specs)
	{
		BE_INFO("Hello Sangenpai!");
	}

	Application::~Application()
	{
		BE_INFO("Goodbye Sangenpai!");
	}
}