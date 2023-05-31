#ifndef BE_INDEX_BUFFER_HPP
#define BE_INDEX_BUFFER_HPP

#	include <Beryllium/API.hpp>
#	include <stdint.h>

namespace Beryllium
{
	class BE_API IndexBuffer
	{
	public:
		IndexBuffer(uint32_t _count);
		virtual ~IndexBuffer();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		uint32_t GetCount() const;
	protected: 
		unsigned int m_rendererId;
		uint32_t m_count;
	};
}

#endif