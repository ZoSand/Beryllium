#ifndef BE_INDEX_BUFFER_HPP
#define BE_INDEX_BUFFER_HPP

#	include <Beryllium/API.hpp>
#	include <stdint.h>

namespace Beryllium
{
	class BE_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static IndexBuffer* Create(uint32_t* _indices, uint32_t _size);
	};
}

#endif