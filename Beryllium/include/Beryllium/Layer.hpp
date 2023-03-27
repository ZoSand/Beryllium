#ifndef BE_LAYER_HPP
#define BE_LAYER_HPP

#include <Beryllium/API.hpp>
#include <Beryllium/Events/EventListener.hpp>

namespace Beryllium
{
	class BE_API Layer : public Beryllium::EventListener
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual bool OnEvent(Event& _event) override;
	};
}

#endif // BE_LAYER_HPP