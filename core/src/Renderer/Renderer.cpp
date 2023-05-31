#include <Beryllium/Renderer/Renderer.hpp>

namespace Beryllium
{
	void Renderer::Set(Renderer* _api)
	{
		s_renderer.reset(_api);
	}

	Renderer* Renderer::Get()
	{
		return s_renderer.get();
	}
	std::unique_ptr<Renderer> Renderer::s_renderer = nullptr;
}