#ifndef BE_BUFFER_LAYOUT_HPP
#define BE_BUFFER_LAYOUT_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Renderer/BufferElement.hpp>

#	include <initializer_list>
#	include <vector>

namespace Beryllium
{
	/// <summary>
	/// Shader variables layout
	/// </summary>
	class BE_API BufferLayout
	{
	public:
		BufferLayout() : m_stride(0) {};
		/// <summary>
		/// Constructor using an initializer list
		/// </summary>
		/// <param name="_elements">the layout to apply</param>
		BufferLayout(const std::initializer_list<BufferElement>& _elements);
		
		/// <summary>
		/// Gets the stride. This will be put in vertex attribute pointer
		/// </summary>
		/// <returns>The stride for this layout</returns>
		uint32_t GetStride() const;
		
		/// <summary>
		/// Returns the list of elements in buffer layout, in order
		/// </summary>
		/// <returns></returns>
		const std::vector<BufferElement>& GetElements() const;

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