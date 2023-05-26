#include <Beryllium/Renderer/Renderer.hpp>

namespace Beryllium
{

	RenderApi Renderer::GetRenderApi()
	{
		return s_renderApi;
	}

	void Renderer::SetRenderApi(RenderApi _api)
	{
		s_renderApi = _api;
	}

	RenderApi Renderer::s_renderApi = RenderApi::None;
}