#include <Beryllium/Renderer/RenderCommand.hpp>

namespace Beryllium
{

	void RenderCommand::Clear()
	{
		Renderer::Clear();
	}

	void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& _array)
	{
		Renderer::DrawIndexed(_array);
	}
}