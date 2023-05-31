#ifndef BE_OPENGL_INDEX_BUFFER_HPP
#define BE_OPENGL_INDEX_BUFFER_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Renderer/IndexBuffer.hpp>

namespace Beryllium
{
	class BE_API OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* _indices, uint32_t _count);
		~OpenGLIndexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;
	};
}

#endif