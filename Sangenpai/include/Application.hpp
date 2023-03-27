#ifndef	SGP_APPLICATION_HPP
#define	SGP_APPLICATION_HPP

#	include <Beryllium.hpp>

namespace Sangenpai
{
	class Application : public Beryllium::Application
	{
	public:
		Application(Beryllium::ApplicationSpecs _specs);
		~Application();
	};
}

#endif // SGP_APPLICATION_HPP