#include <Beryllium/Platforms/OpenGL/OpenGLIndexBuffer.hpp>

#include <Beryllium/Logger.hpp>

#include <glad/glad.h>

namespace Beryllium
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* _indices, uint32_t _count)
		: IndexBuffer(_count)
	{
		::glCreateBuffers(1, &m_rendererId);
		Bind();
		::glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(uint32_t), _indices, GL_STATIC_DRAW);
		BE_TRACE("[OpenGL][Index Buffer] Created Index Buffer {%u}", m_rendererId);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		::glDeleteBuffers(1, &m_rendererId);
		BE_TRACE("[OpenGL][Index Buffer] Destroyed Index Buffer {%u}", m_rendererId);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}