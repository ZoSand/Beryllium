#ifndef BE_SHADER_DATA_TYPE_HPP
#define BE_SHADER_DATA_TYPE_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Logger.hpp>
#	include <cstdint>
#	include <stdexcept>

namespace Beryllium
{
	enum class BE_API ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Int2,
		Int3,
		Int4,
		Mat3,
		Mat4
	}; //TODO: add missing unsigned integers, see https://www.khronos.org/opengl/wiki/Data_Type_(GLSL)

	uint32_t ShaderDataTypeSize(ShaderDataType _type);
}

#endif