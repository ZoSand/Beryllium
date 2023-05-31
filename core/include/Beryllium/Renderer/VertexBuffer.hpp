#ifndef BE_VERTEX_BUFFER_HPP
#define BE_VERTEX_BUFFER_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Renderer/BufferLayout.hpp>
#	include <stdint.h>

namespace Beryllium
{
	class BE_API VertexBuffer
	{
	public:
		VertexBuffer(uint32_t _count);
		virtual ~VertexBuffer();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& _layout) = 0;

		uint32_t GetCount() const;
	protected:
		unsigned int m_rendererId;
		uint32_t m_count;
		BufferLayout m_layout;
	};
}

#endif