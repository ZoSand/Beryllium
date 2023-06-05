#include <Beryllium/Layer.hpp>

namespace Beryllium
{
	Layer::Layer()
	{}

	Layer::~Layer()
	{}

	void Layer::OnAttach()
	{}

	void Layer::OnDetach()
	{}

	void Layer::OnUpdate()
	{}

	void Layer::OnRender()
	{
	}

	bool Layer::OnEvent(Event& _event)
	{
		return false;
	}
}
