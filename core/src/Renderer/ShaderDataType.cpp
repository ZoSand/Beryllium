#include <Beryllium/Renderer/ShaderDataType.hpp>

namespace Beryllium
{
	uint32_t ShaderDataTypeSize(ShaderDataType _type)
	{
		switch (_type)
		{
		case Beryllium::ShaderDataType::Float:
			return 1 * sizeof(float);
		case Beryllium::ShaderDataType::Float2:
			return 2 * sizeof(float);
		case Beryllium::ShaderDataType::Float3:
			return 3 * sizeof(float);
		case Beryllium::ShaderDataType::Float4:
			return 4 * sizeof(float);
		case Beryllium::ShaderDataType::Int:
			return 1 * sizeof(int);
		case Beryllium::ShaderDataType::Int2:
			return 2 * sizeof(int);
		case Beryllium::ShaderDataType::Int3:
			return 3 * sizeof(int);
		case Beryllium::ShaderDataType::Int4:
			return 4 * sizeof(int);
		case Beryllium::ShaderDataType::Mat3:
			return 3 * 3 * sizeof(float);
		case Beryllium::ShaderDataType::Mat4:
			return 4 * 4 * sizeof(float);
		default:
			BE_CRITICAL("Unknown shader data type");
			throw std::runtime_error("Unknown Shader data type");
		}
	}

}