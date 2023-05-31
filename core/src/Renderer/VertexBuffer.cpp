#include <Beryllium/Renderer/VertexBuffer.hpp>

#include <Beryllium/Renderer/Renderer.hpp>
#include <Beryllium/Platforms/OpenGL/OpenGLVertexBuffer.hpp>

#include <Beryllium/Logger.hpp>

#include <stdexcept>

namespace Beryllium
{
	VertexBuffer::VertexBuffer(uint32_t _count)
		: m_count(_count)
		, m_rendererId(0)
	{}
	VertexBuffer::~VertexBuffer() {}

	uint32_t VertexBuffer::GetCount() const
	{
		return m_count;
	}

}