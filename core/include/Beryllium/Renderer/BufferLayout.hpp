#ifndef BE_BUFFER_LAYOUT_HPP
#define BE_BUFFER_LAYOUT_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Renderer/BufferElement.hpp>

#	include <initializer_list>
#	include <vector>

namespace Beryllium
{
	class BE_API BufferLayout
	{
	public:
		BufferLayout() : m_stride(0) {};
		BufferLayout(const std::initializer_list<BufferElement>& _elements);
		
		uint32_t GetStride() const;
		
		inline const std::vector<BufferElement>& GetElements() const;

		std::vector<BufferElement>::iterator begin();
		std::vector<BufferElement>::iterator end();
		std::vector<BufferElement>::const_iterator begin() const;
		std::vector<BufferElement>::const_iterator end() const;

	private:
		std::vector<BufferElement> m_elements;
		uint32_t m_stride;
	};
}

#endif