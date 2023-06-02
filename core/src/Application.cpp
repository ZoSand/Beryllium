#include <Beryllium/Application.hpp>
#include <Beryllium/Logger.hpp>
#include <Beryllium/Events/CommonEvents.hpp>

#include <Beryllium/Renderer/BufferLayout.hpp>
#include <Beryllium/Renderer/Renderer.hpp>
#include <Beryllium/Renderer/RenderCommand.hpp>

#include <iostream>
#include <string>

#include <imgui.h>


#	if defined(BE_PLATFORM_WINDOWS)
#		include <Beryllium/Platforms/Windows/WindowsWindow.hpp>
#	else
#		error "Beryllium Window is only implemented on Windows!"
#	endif

//#include <glad/glad.h>

namespace Beryllium
{
	Application* Application::s_application = nullptr;

	Application::Application(const Beryllium::ApplicationSpecs& _specs)
		: m_specs(_specs)
	{
		Beryllium::Logger::Init();

		if (Application::Get() != nullptr)
		{
			BE_CRITICAL("[System][Application] Only one application can be created at a time");
			throw std::runtime_error("Only one application can be created at a time");
		}

		//if renderer is not set by user, use OpenGL by default
		if (_specs.renderer == nullptr)
		{
			BE_CRITICAL("[System][Application] A renderer needs to be set in Application Specs");
			throw std::runtime_error("A renderer needs to be set in Application Specs");
		}

		Application::Set(this);
		Renderer::Set(_specs.renderer);

		//WARNING: platform specific code 
#if defined(BE_PLATFORM_WINDOWS)
		m_window = std::make_unique<WindowsWindow>(_specs.name, std::make_pair<float, float>(1280, 720));
#else
#	error "Beryllium is missing a window for this platform"
#endif

		m_window->AddListener(this);

		m_context.reset(Renderer::CreateGraphicsContext(m_window.get()));
		m_context->Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	};

	Application::~Application()
	{
		m_context->Destroy();
		m_layerStack.~LayerStack();
		Logger::Shutdown();
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

	static const char* current_item = "Fill";

	void Application::Run()
	{
		while (m_window->IsOpen())
		{
			m_window->OnUpdate();
			//swap buffers
			m_context->SwapBuffers();

			Renderer::BeginScene();
			RenderCommand::Clear();

			for (Beryllium::Layer* layer : m_layerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			{
				{
					ImGui::Begin("Debug Info");
					ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
					ImGui::Text("Active Renderer: %s", std::string(typeid(*Renderer::Get()).name()).substr(std::string("class Beryllium::").length()).c_str());
					{
					/*
						//change fill mode for OpenGL Polygons 
						if (ImGui::BeginCombo("Render Mode", current_item))
						{
							if (ImGui::Selectable("Point", current_item == "Point")) {
								current_item = "Point";
								::glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
							}
							if (current_item == "Point")
							{
								ImGui::SetItemDefaultFocus();
							}

							if (ImGui::Selectable("Wire Frame", current_item == "WireFrame")) {
								current_item = "WireFrame";
								::glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
							}
							if (current_item == "WireFrame")
							{
								ImGui::SetItemDefaultFocus();
							}

							if (ImGui::Selectable("Fill", current_item == "Fill")) {
								current_item = "Fill";
								::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
							}
							if (current_item == "Fill")
							{
								ImGui::SetItemDefaultFocus();
							}
							ImGui::EndCombo();
						}
					*/
					}
					ImGui::End();
				}
			}
			m_ImGuiLayer->End();

			Renderer::EndScene();
		}
	}

	bool Application::OnEvent(Beryllium::Event& _event)
	{
		//BE_TRACE("Event: %s", typeid(_event).name());
		if (_event.Is<Beryllium::Events::WindowClosed>())
		{
			m_window->Close();
			return true;
		}
		else if (_event.Is<Beryllium::Events::WindowFocusChanged>())
		{
			if (_event.As<Beryllium::Events::WindowFocusChanged>().IsFocused()) {
				BE_TRACE("[System][Window] Get focus");
			}
			else {
				BE_TRACE("[System][Window] Lost focus");
			}
		}

		else if (_event.Is<Beryllium::Events::WindowResized>())
		{
			Renderer::SetViewport(m_window->GetSize());
		}

		for (auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it)
		{
			if ((*it)->OnEvent(_event))
			{
				//BE_TRACE("Event %s handled by layer %s", typeid(_event).name(), typeid(**it).name());
				return true;
			}
		}

		return false;
	}
}