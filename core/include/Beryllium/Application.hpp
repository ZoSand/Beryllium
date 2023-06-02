#ifndef BE_APPLICATION_HPP
#define BE_APPLICATION_HPP

//api
#	include <Beryllium/API.hpp>

//event system
#	include <Beryllium/Events/Event.hpp>
#	include <Beryllium/Events/EventListener.hpp>

//IO
#	include <Beryllium/Window.hpp>
#	include <Beryllium/Keyboard.hpp>
#	include <Beryllium/Mouse.hpp>

//layers
#	include <Beryllium/Layer.hpp>
#	include <Beryllium/LayerStack.hpp>

//rendering
#	include <Beryllium/Renderer/Shader.hpp>
#	include <Beryllium/Renderer/GraphicsContext.hpp>
#	include <Beryllium/Renderer/VertexArray.hpp>
#	include <Beryllium/Renderer/Renderer.hpp>

//specific code
#	include <Beryllium/Layers/ImGuiLayer.hpp>

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
		Beryllium::Renderer* renderer;
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

		//get application instance
		static Application* Get();

		//get window
		const Beryllium::Window* GetWindow() const;

		// push a layer to the layer stack
		void PushLayer(Beryllium::Layer* _layer);
		void PushOverlay(Beryllium::Layer* _overlay);

		// pop a layer from the layer stack
		void PopLayer(Beryllium::Layer* _layer);
		void PopOverlay(Beryllium::Layer* _overlay);

		// run the application
		void Run();

	private:
		static Application* s_application;

		Beryllium::ApplicationSpecs m_specs;

		std::unique_ptr<Beryllium::Window> m_window = nullptr;

		Beryllium::LayerStack m_layerStack;
		Beryllium::ImGuiLayer* m_ImGuiLayer;

		//TODO: define classes
		std::shared_ptr<Beryllium::VertexArray> m_vertexArray;
		std::shared_ptr<Beryllium::Shader> m_shader;

		std::shared_ptr<Beryllium::GraphicsContext> m_context;

		static void Set(Application* _application);

	protected:
		virtual bool OnEvent(Beryllium::Event& _event) override;
	};

	Application* CreateApplication(CmdArgs _args);
}

#endif // BE_APPLICATION_HPP