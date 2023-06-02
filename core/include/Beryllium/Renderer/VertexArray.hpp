#ifndef BE_VERTEX_ARRAY_HPP
#define BE_VERTEX_ARRAY_HPP

#	include <Beryllium/API.hpp>

#	include <Beryllium/Renderer/IndexBuffer.hpp>
#	include <Beryllium/Renderer/VertexBuffer.hpp>

namespace Beryllium
{
	class BE_API VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> _vertexBuffer) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> _indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const;
		virtual const IndexBuffer* GetIndexBuffer() const;

	protected:
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
		std::shared_ptr<IndexBuffer> m_indexBuffer;
		uint32_t m_rendererID;
	};
}

#endif