#ifndef BE_LAYER_STACK_HPP
#define BE_LAYER_STACK_HPP

#include <Beryllium/API.hpp>
#include <Beryllium/Layer.hpp>
#include <Beryllium/Events/Event.hpp>
#include <Beryllium/Events/EventDispatcher.hpp>

#include <vector>

namespace Beryllium
{
	class BE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* _layer);
		void PushOverlay(Layer* _overlay);
		void PopLayer(Layer* _layer);
		void PopOverlay(Layer* _overlay);

		std::vector<Layer*>::iterator begin();
		std::vector<Layer*>::iterator end();
		std::vector<Layer*>::reverse_iterator rbegin();
		std::vector<Layer*>::reverse_iterator rend();

		std::vector<Layer*>::const_iterator begin() const;
		std::vector<Layer*>::const_iterator end() const;
		std::vector<Layer*>::const_reverse_iterator rbegin() const;
		std::vector<Layer*>::const_reverse_iterator rend() const;

	private:
		std::vector<Layer*> m_layers;
		unsigned int  m_layerInsertIt;
	};
}

#endif // BE_LAYER_STACK_HPP