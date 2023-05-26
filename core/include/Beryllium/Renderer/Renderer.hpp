#ifndef BE_RENDERER_HPP
#define BE_RENDERER_HPP

#	include <Beryllium/API.hpp>

namespace Beryllium
{
	enum class BE_API RenderApi
	{
		None = 0,
		OpenGL = 1,
		//TODO: add render api?
	};

	class BE_API Renderer
	{
	public:
		static RenderApi GetRenderApi();
		static void SetRenderApi(RenderApi _api);

	private:
		static RenderApi s_renderApi;
	};
}

#endif