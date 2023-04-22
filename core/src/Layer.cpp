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

	bool Layer::OnEvent(Event& _event)
	{
		return false;
	}
}
