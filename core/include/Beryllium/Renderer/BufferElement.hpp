#ifndef BE_BUFFER_ELEMENT_HPP
#define BE_BUFFER_ELEMENT_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Renderer/ShaderDataType.hpp>

#	include <string>

namespace Beryllium
{
	/// <summary>
	/// Shader variable element description for declaring layout
	/// </summary>
	struct BE_API BufferElement
	{
		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;
		bool normalized;

		BufferElement(ShaderDataType _type, const std::string& _name, bool _normalized = false);
		uint32_t GetComponentCount() const;
	};
}


#endif