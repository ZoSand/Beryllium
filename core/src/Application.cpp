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

#include <glad/glad.h>

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

		//TODO: move to dedicated VertexArray
		::glGenVertexArrays(1, &m_vertexArray);
		::glBindVertexArray(m_vertexArray);

		//TODO: move to dedicated VertexBuffer
		::glGenBuffers(1, &m_vertexBuffer);
		::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

		float vertices[3 * 3] = {
			-.5f, -.5f, 0.f,
			.5f, -.5f, 0.f,
			0.f, .5f, 0.f
		};
		::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		::glEnableVertexAttribArray(0);
		::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		//TODO: move to dedicated IndexBuffer
		::glGenBuffers(1, &m_indexBuffer);
		::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};
		::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
			//TODO: move to dedicated
			::glClearColor(0.f, .63f, .56f, 1.f);
			::glClear(GL_COLOR_BUFFER_BIT);

			auto [width, height] = m_window->GetSize();
			::glViewport(0, 0, width, height);

			//TODO: move to dedicated
			::glBindVertexArray(m_vertexArray);
			::glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
			return true;
		}
		else if (_event.Is<Beryllium::Events::WindowFocusChanged>())
		{
			if (_event.As<Beryllium::Events::WindowFocusChanged>().IsFocused()) {
				BE_TRACE("[Window] Get focus");
			}
			else {
				BE_TRACE("[Window] Lost focus");
			}
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