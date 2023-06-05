#include <Beryllium/Application.hpp>
#include <Beryllium/Logger.hpp>
#include <Beryllium/Time.hpp>
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
	Beryllium::Application* Beryllium::Application::s_application = nullptr;

	Beryllium::Application::Application(const Beryllium::ApplicationSpecs& _specs)
		: m_specs(_specs)
	{
		Beryllium::Logger::Init();

		if (Beryllium::Application::Get() != nullptr)
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

		Beryllium::Application::Set(this);
		Beryllium::Renderer::Set(_specs.renderer);

		//WARNING: platform specific code 
#if defined(BE_PLATFORM_WINDOWS)
		m_window = std::make_unique<Beryllium::WindowsWindow>(_specs.name, std::make_pair<float, float>(1280, 720));
#else
#	error "Beryllium is missing a window for this platform"
#endif

		m_window->AddListener(this);

		m_context.reset(Beryllium::Renderer::CreateGraphicsContext(m_window.get()));
		m_context->Init();

		m_ImGuiLayer = new Beryllium::ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	};

	Beryllium::Application::~Application()
	{
		m_context->Destroy();
		m_layerStack.~LayerStack();
		Beryllium::Logger::Shutdown();
	}

	Beryllium::Application* Beryllium::Application::Get()
	{
		return s_application;
	}

	void Beryllium::Application::Set(Beryllium::Application* _app)
	{
		s_application = _app;
	}

	const Beryllium::Window* Beryllium::Application::GetWindow() const
	{
		return m_window.get();
	}

	void Beryllium::Application::PushLayer(Beryllium::Layer* _layer)
	{
		m_layerStack.PushLayer(_layer);
	}

	void Beryllium::Application::PushOverlay(Beryllium::Layer* _overlay)
	{
		m_layerStack.PushOverlay(_overlay);
	}

	void Beryllium::Application::PopLayer(Beryllium::Layer* _layer)
	{
		m_layerStack.PopLayer(_layer);
	}

	void Beryllium::Application::PopOverlay(Beryllium::Layer* _overlay)
	{
		m_layerStack.PopOverlay(_overlay);
	}

	static const char* current_item = "Fill";

	void Beryllium::Application::Run()
	{
		while (m_window->IsOpen())
		{
			Beryllium::Time::Tick();

			Beryllium::RenderCommand::Clear();
			m_window->OnUpdate();

			for (Beryllium::Layer* layer : m_layerStack)
			{
				layer->OnUpdate();
			}

			for (Beryllium::Layer* layer : m_layerStack)
			{
				layer->OnRender();
			}

			m_ImGuiLayer->Begin();
			{
				{
					ImGui::Begin("Debug Info");
					ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
					ImGui::Text("Active Renderer: %s", std::string(typeid(*Beryllium::Renderer::Get()).name()).substr(std::string("class Beryllium::").length()).c_str());
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

			//at the end of rendering, swap buffers
			m_context->SwapBuffers();
		}
	}

	bool Beryllium::Application::OnEvent(Beryllium::Event& _event)
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
			auto& [w, h] = m_window->GetSize();
			Beryllium::Renderer::SetViewport({ w, h });
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