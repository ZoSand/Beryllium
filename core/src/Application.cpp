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
		Beryllium::Logger::SetLevel(LogLevel::Trace);

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
		/*float vertices[4 * 3] = {
			-1.f, -1.f, 0.f,
			1.f, -1.f, 0.f,
			1.f, 1.f, 0.f,
			-1.f, 1.f, 0.f
		};*/
		::glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		::glEnableVertexAttribArray(0);
		::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		//TODO: move to dedicated IndexBuffer
		::glGenBuffers(1, &m_indexBuffer);
		::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};
		 /*unsigned int indices[3 * 2] = {
			0, 1, 2,
			0, 2, 3
		};*/
		::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 i_Position;
			out vec3 t_Position;

			void main()
			{
				gl_Position = vec4(i_Position, 1.0);
				t_Position = i_Position; 
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;
			in vec3 t_Position;

			vec4 remap(vec4 _val, vec2 _min, vec2 _max)
			{
				return _max.x + (_val - _min.x) * (_max.y -  _max.x) / (_min.y - _min.x);
			}

			void main()
			{
				o_Color = vec4(0.8, 0.2, 0.3, 0.5);
				o_Color = remap(vec4(t_Position, 0.5), vec2(-1, 1), vec2(0, 1));
			}
		)";

		m_shader = std::make_unique<Beryllium::Shader>(vertexSrc, fragmentSrc);
	};

	Application::~Application()
	{
		m_layerStack.~LayerStack();
		Beryllium::Logger::Shutdown();
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

	static const char* current_item = NULL;

	void Application::Run()
	{
		while (m_window->IsOpen())
		{
			m_window->OnUpdate();
			//TODO: move to dedicated
			::glClearColor(0.f, .63f, .56f, 1.f);
			::glClear(GL_COLOR_BUFFER_BIT);

			m_shader->Bind();

			auto [width, height] = m_window->GetSize();
			::glViewport(0, 0, width, height);

			//TODO: move to dedicated
			::glBindVertexArray(m_vertexArray);
			::glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			//::glDrawElements(GL_TRIANGLES, 3 * 2, GL_UNSIGNED_INT, nullptr);

			for (Beryllium::Layer* layer : m_layerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			{
				if (showDemo) 
				{
					ImGui::ShowDemoWindow(&showDemo);
				}

				{
					ImGui::Begin("Debug Info");
					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
					{
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
					}
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
				BE_TRACE("[System][Window] Get focus");
			}
			else {
				BE_TRACE("[System][Window] Lost focus");
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