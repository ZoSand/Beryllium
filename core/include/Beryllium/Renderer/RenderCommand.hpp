#ifndef BE_RENDER_COMMAND_HPP
#define BE_RENDER_COMMAND_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Renderer/VertexArray.hpp>
#	include <Beryllium/Renderer/Renderer.hpp>

namespace Beryllium
{
	class BE_API RenderCommand
	{
	public:
		//TODO: Set Clear Color
		static void Clear();
		static void DrawIndexed(const std::shared_ptr<VertexArray>& _array);

	private:
		Renderer* s_renderer;
	};
}

#endif // BE_RENDER_COMMAND_HPP
