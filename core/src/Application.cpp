#include <Beryllium/Application.hpp>
#include <Beryllium/Logger.hpp>
#include <Beryllium/Events/CommonEvents.hpp>

#include <iostream>
#include <string>

#include <imgui.h>


#	if defined(BE_PLATFORM_WINDOWS)
#		include <Beryllium/Platforms/Windows/WindowsWindow.hpp>
//#		include <Beryllium/Platforms/Windows/WindowsKeyboard.hpp>
//#		include <Beryllium/Platforms/Windows/WindowsMouse.hpp>
#	else
#		error "Beryllium Window is only implemented on Windows!"
#	endif

//TODO: remove
bool showDemo = true;

namespace Beryllium
{
	Application* Application::s_application = nullptr;

	Application::Application(const Beryllium::ApplicationSpecs& _specs)
		: m_specs(_specs)
	{
		Beryllium::Logger::Init();

		if (Application::Get() != nullptr)
		{
			BE_CRITICAL("Only one application can be created at a time");
			throw std::runtime_error("Only one application can be created at a time");
		}

		Application::Set(this);

		//WARNING: platform specific code 
#if defined(BE_PLATFORM_WINDOWS)
		m_window = std::make_unique<WindowsWindow>(_specs.name, 1280, 720);
#else
#	error "Beryllium is missing a window for this platform"
#endif
		m_window->AddListener(this);

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	};

	Application::~Application()
	{
		Beryllium::Logger::Shutdown();
		m_layerStack.~LayerStack();
	}

	Application* Application::Get()
	{
		return s_application;
	}

	void Application::Set(Application* _app)
	{
		s_application = _app;
	}

	const Beryllium::Window* Application::GetWindow() const
	{
		return m_window.get();
	}

	void Application::PushLayer(Beryllium::Layer* _layer)
	{
		m_layerStack.PushLayer(_layer);
	}

	void Application::PushOverlay(Beryllium::Layer* _overlay)
	{
		m_layerStack.PushOverlay(_overlay);
	}

	void Application::PopLayer(Beryllium::Layer* _layer)
	{
		m_layerStack.PopLayer(_layer);
	}

	void Application::PopOverlay(Beryllium::Layer* _overlay)
	{
		m_layerStack.PopOverlay(_overlay);
	}

	void Application::Run()
	{
		while (m_window->IsOpen())
		{
			m_window->OnUpdate();

			for (Beryllium::Layer* layer : m_layerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			{
				if (showDemo) {
					ImGui::ShowDemoWindow(&showDemo);
				}


				{
					ImGui::Begin("Debug Info");
					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
					ImGui::End();
				}
			}
			m_ImGuiLayer->End();
		}
	}

	bool Application::OnEvent(Beryllium::Event& _event)
	{
		//BE_TRACE("Event: %s", typeid(_event).name());
		if (_event.Is<Beryllium::Events::WindowClosed>())
		{
			m_window->Close();
			BE_TRACE("Window closed");
			return true;
		}

		for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
		{
			if ((*it)->OnEvent(_event))
			{
				BE_TRACE("Event %s handled by layer %s", typeid(_event).name(), typeid(**it).name());
				return true;
			}
		}

		return false;
	}
}