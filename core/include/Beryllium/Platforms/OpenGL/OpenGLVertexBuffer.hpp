#ifndef BE_OPENGL_VERTEX_BUFFER_HPP
#define BE_OPENGL_VERTEX_BUFFER_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Renderer/VertexBuffer.hpp>

namespace Beryllium
{
	class BE_API OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* _vertices, uint32_t _count);
		~OpenGLVertexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		const BufferLayout& GetLayout() const override;
		void SetLayout(const BufferLayout& _layout) override;

	};
}

#endif