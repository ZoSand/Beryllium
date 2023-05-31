#include <Beryllium/Renderer/IndexBuffer.hpp>

#include <Beryllium/Renderer/Renderer.hpp>
#include <Beryllium/Platforms/OpenGL/OpenGLIndexBuffer.hpp>

#include <Beryllium/Logger.hpp>

#include <stdexcept>

namespace Beryllium
{

	IndexBuffer::IndexBuffer(uint32_t _count)
		: m_count(_count)
		, m_rendererId(0)
	{}

	IndexBuffer::~IndexBuffer() {}
	
	uint32_t IndexBuffer::GetCount() const
	{
		return m_count;
	}

}