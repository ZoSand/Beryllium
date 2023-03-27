#ifndef BE_APPLICATION_HPP
#define BE_APPLICATION_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Events/Event.hpp>
#	include <Beryllium/Events/EventListener.hpp>

#	include <Beryllium/Layer.hpp>
#	include <Beryllium/LayerStack.hpp>

#	if defined(BE_PLATFORM_WINDOWS)
#		include <Beryllium/Platforms/Windows/WindowsWindow.hpp>
#	else
#		error "Beryllium Window is only implemented on Windows!"
#	endif

#	include <string>

namespace Beryllium
{
	struct CmdArgs
	{
		int argc;
		char** argv;
	};

	struct ApplicationSpecs
	{
		std::string name;
		Beryllium::CmdArgs args;
	};

	class BE_API Application : public Beryllium::EventListener
	{
	public:
		// Constructor and destructor
		Application(const Beryllium::ApplicationSpecs& _specs);
		virtual ~Application();

		//delete copy constructor and assignment operator
		Application(const Beryllium::Application&) = delete;
		Application(const Beryllium::Application&&) = delete;
		Application& operator=(const Beryllium::Application&) = delete;
		Application& operator=(const Beryllium::Application&&) = delete;

		// push a layer to the layer stack
		void PushLayer(Beryllium::Layer* _layer);
		void PushOverlay(Beryllium::Layer* _overlay);

		// pop a layer from the layer stack
		void PopLayer(Beryllium::Layer* _layer);
		void PopOverlay(Beryllium::Layer* _overlay);
		
		// run the application
		void Run();

	private:
		Beryllium::Window* m_window = nullptr;
		Beryllium::ApplicationSpecs m_specs;
		Beryllium::LayerStack m_layerStack;

		virtual bool OnEvent(Beryllium::Event& _event) override;
	};

	Application* CreateApplication(CmdArgs _args);
}

#endif // BE_APPLICATION_HPP