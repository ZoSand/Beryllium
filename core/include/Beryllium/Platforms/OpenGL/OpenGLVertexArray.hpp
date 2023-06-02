#ifndef BE_OPENGL_VERTEX_ARRAY_HPP
#define BE_OPENGL_VERTEX_ARRAY_HPP

#	include <Beryllium/API.hpp>

#	include <Beryllium/Renderer/VertexArray.hpp>

namespace Beryllium
{
	class BE_API OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> _vertexBuffer) override;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> _indexBuffer) override;
	};
}

#endif