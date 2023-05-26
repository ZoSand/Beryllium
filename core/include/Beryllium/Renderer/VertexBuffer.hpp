#ifndef BE_VERTEX_BUFFER_HPP
#define BE_VERTEX_BUFFER_HPP

#	include <Beryllium/API.hpp>
#	include <stdint.h>

namespace Beryllium
{
	class BE_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* _vertices, uint32_t _size);
	};
}

#endif