#include <Beryllium/Renderer/BufferElement.hpp>

namespace Beryllium
{

	BufferElement::BufferElement(ShaderDataType _type, const std::string& _name, bool _normalized)
		: name(_name)
		, type(_type)
		, size(ShaderDataTypeSize(_type))
		, offset(0)
		, normalized(_normalized)
	{
	}

	uint32_t BufferElement::GetComponentCount() const
	{
		switch (type)
		{
		case Beryllium::ShaderDataType::Float:
		case Beryllium::ShaderDataType::Int:
			return 1;
		case Beryllium::ShaderDataType::Float2:
		case Beryllium::ShaderDataType::Int2:
			return 2;
		case Beryllium::ShaderDataType::Float3:
		case Beryllium::ShaderDataType::Int3:
			return 3;
		case Beryllium::ShaderDataType::Float4:
		case Beryllium::ShaderDataType::Int4:
			return 4;
		case Beryllium::ShaderDataType::Mat3:
			return 3 * 3;
		case Beryllium::ShaderDataType::Mat4:
			return 4 * 4;
		default:
			BE_CRITICAL("Unknown shader data type");
			throw std::runtime_error("Unknown Shader data type");
		}
	}

}