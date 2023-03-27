#include <Beryllium/Application.hpp>
#include <Beryllium/Logger.hpp>
#include <Beryllium/Events/CommonEvents.hpp>

#include <iostream>
#include <string>

namespace Beryllium
{
	Application::Application(const Beryllium::ApplicationSpecs& _specs)
		: m_specs(_specs)
	{
		Beryllium::Logger::Init();
		m_window = CreateApplicationWindow(_specs.name, 1280, 720);

		m_window->AddListener(this);

		m_window->Open();
	};

	Application::~Application()
	{
		Beryllium::Logger::Shutdown();
		delete m_window;
	}

	void Application::PushLayer(Beryllium::Layer* _layer)
	{
		m_layerStack.PushLayer(_layer);
		m_window->AddListener(_layer);
		_layer->OnAttach();
	}

	void Application::PushOverlay(Beryllium::Layer* _overlay)
	{
		m_layerStack.PushOverlay(_overlay);
		m_window->AddListener(_overlay);
		_overlay->OnAttach();
	}

	void Application::PopLayer(Beryllium::Layer* _layer)
	{
		m_layerStack.PopLayer(_layer);
		m_window->RemoveListener(_layer);
		_layer->OnDetach();
	}

	void Application::PopOverlay(Beryllium::Layer* _overlay)
	{
		m_layerStack.PopOverlay(_overlay);
		m_window->RemoveListener(_overlay);
		_overlay->OnDetach();
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
		}
	}

	bool Application::OnEvent(Beryllium::Event& _event)
	{
		Logger::Trace("Event: %s", typeid(_event).name());

		if (_event.Is<Beryllium::Events::WindowClosed>())
		{
			m_window->Close();
			Logger::Trace("Window closed");
			return true;
		}
		return false;
	}
}