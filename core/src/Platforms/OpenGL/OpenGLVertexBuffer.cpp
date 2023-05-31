#include <Beryllium/Platforms/OpenGL/OpenGLVertexBuffer.hpp>

#include <Beryllium/Logger.hpp>

#include <glad/glad.h>

namespace Beryllium
{
	GLenum GetGlType(ShaderDataType _type)
	{
		switch (_type)
		{
		case Beryllium::ShaderDataType::Float:
		case Beryllium::ShaderDataType::Float2:
		case Beryllium::ShaderDataType::Float3:
		case Beryllium::ShaderDataType::Float4:
		case Beryllium::ShaderDataType::Mat3:
		case Beryllium::ShaderDataType::Mat4:
			return GL_FLOAT;
		case Beryllium::ShaderDataType::Int:
		case Beryllium::ShaderDataType::Int2:
		case Beryllium::ShaderDataType::Int3:
		case Beryllium::ShaderDataType::Int4:
			return GL_INT;
			break;
			break;
		default:
			BE_CRITICAL("Unknown Shader data type");
			throw std::runtime_error("Unknown Shader data type");
		}
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* _vertices, uint32_t _count)
		: VertexBuffer(_count)
	{
		::glCreateBuffers(1, &m_rendererId);
		Bind();
		::glBufferData(GL_ARRAY_BUFFER, _count * sizeof(float), _vertices, GL_STATIC_DRAW);
		BE_TRACE("[OpenGL][Vertex Buffer] Created Vertex Buffer {%u}", m_rendererId);

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		::glDeleteBuffers(1, &m_rendererId);
		BE_TRACE("[OpenGL][Vertex Buffer] Destroyed Vertex Buffer {%u}", m_rendererId);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		::glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		::glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	const Beryllium::BufferLayout& OpenGLVertexBuffer::GetLayout() const
	{
		return m_layout;
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& _layout)
	{
		uint32_t count = 0;
		for (auto& element : _layout)
		{
			::glEnableVertexAttribArray(count);
			::glVertexAttribPointer(
				count,
				element.GetComponentCount(),
				Beryllium::GetGlType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				_layout.GetStride(),
				(const void*)element.offset
			);
			count++;
		}
		m_layout = _layout;
	}

}