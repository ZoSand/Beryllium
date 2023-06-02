#include <Beryllium/Platforms/OpenGL/OpenGLVertexArray.hpp>

#include <glad/glad.h>

namespace Beryllium
{
	::GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType _type)
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
		default:
			BE_CRITICAL("[OpenGL][ShaderDataTypeToOpenGLBaseType] Unknown ShaderDataType!");
			throw std::runtime_error("Unknown ShaderDataType!");
			break;
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		::glCreateVertexArrays(1, &m_rendererID);
	}
	
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		::glDeleteVertexArrays(1, &m_rendererID);
	}
	
	void OpenGLVertexArray::Bind() const
	{
		::glBindVertexArray(m_rendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		::glBindVertexArray(0);
	}
	
	void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> _vertexBuffer)
	{
		if (_vertexBuffer->GetLayout().GetElements().size() == 0)
		{
			BE_CRITICAL("[OpengGL][Vertex Array] Vertex Buffer has no layout!");
			throw std::runtime_error("Vertex Buffer has no layout!");
		}

		::glBindVertexArray(m_rendererID);
		_vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = _vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			::glEnableVertexAttribArray(index);
			::glVertexAttribPointer(
				index, 
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type), 
				element.normalized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(), 
				(const void*)element.offset
			);
			index++;
		}

		m_vertexBuffers.push_back(_vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> _indexBuffer)
	{
		::glBindVertexArray(m_rendererID);
		_indexBuffer->Bind();

		m_indexBuffer = _indexBuffer;
	}
}