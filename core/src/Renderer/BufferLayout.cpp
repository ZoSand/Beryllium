#include <Beryllium/Renderer/BufferLayout.hpp>

namespace Beryllium
{

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& _elements)
		: m_elements(_elements)
	{
		uint32_t offset = 0;
		m_stride = 0;
		for (auto& element : m_elements)
		{
			element.offset = offset;
			offset += element.size;
			m_stride += element.size;
		}
	}

	uint32_t BufferLayout::GetStride() const
	{
		return m_stride;
	}

	const std::vector<Beryllium::BufferElement>& BufferLayout::GetElements() const
	{
		return m_elements;
	}

	std::vector<BufferElement>::iterator BufferLayout::begin()
	{
		return m_elements.begin();
	}

	std::vector<BufferElement>::const_iterator BufferLayout::begin() const
	{
		return m_elements.begin();
	}

	std::vector<BufferElement>::iterator BufferLayout::end()
	{
		return m_elements.end();
	}

	std::vector<BufferElement>::const_iterator BufferLayout::end() const
	{
		return m_elements.end();
	}

}