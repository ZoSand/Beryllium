#include <Beryllium/Renderer/VertexArray.hpp>

namespace Beryllium
{
	const std::vector<std::shared_ptr<VertexBuffer>>& VertexArray::GetVertexBuffers() const
	{
		return m_vertexBuffers;
	}

	const IndexBuffer* VertexArray::GetIndexBuffer() const
	{
		return m_indexBuffer.get();
	}
}