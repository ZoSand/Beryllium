#include <Beryllium/LayerStack.hpp>

namespace Beryllium
{
	LayerStack::LayerStack()
	{
		
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_layerInsertIt = m_layers.emplace(m_layerInsertIt, layer);
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
			m_layerInsertIt--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
		}
	}

	//iterators
	std::vector<Layer*>::iterator LayerStack::begin()
	{
		return m_layers.begin();
	}

	std::vector<Layer*>::iterator LayerStack::end()
	{
		return m_layers.end();
	}
	
	std::vector<Layer*>::reverse_iterator LayerStack::rbegin()
	{
		return m_layers.rbegin();
	}

	std::vector<Layer*>::reverse_iterator LayerStack::rend()
	{
		return m_layers.rend();
	}

	//const iterators
	std::vector<Layer*>::const_iterator LayerStack::begin() const
	{
		return m_layers.begin();
	}

	std::vector<Layer*>::const_iterator LayerStack::end() const
	{
		return m_layers.end();
	}

	std::vector<Layer*>::const_reverse_iterator LayerStack::rbegin() const
	{
		return m_layers.rbegin();
	}

	std::vector<Layer*>::const_reverse_iterator LayerStack::rend() const
	{
		return m_layers.rend();
	}

	
}