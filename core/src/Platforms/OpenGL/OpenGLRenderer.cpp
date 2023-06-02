#include <Beryllium/Platforms/OpenGL/OpenGLRenderer.hpp>
#include <Beryllium/Platforms/OpenGL/OpenGLGraphicsContext.hpp>
#include <Beryllium/Platforms/OpenGL/OpenGLIndexBuffer.hpp>
#include <Beryllium/Platforms/OpenGL/OpenGLShader.hpp>
#include <Beryllium/Platforms/OpenGL/OpenGLVertexBuffer.hpp>
#include <Beryllium/Platforms/OpenGL/OpenGLVertexArray.hpp>

#include <glad/glad.h>

namespace Beryllium
{
	OpenGLRenderer::OpenGLRenderer()
	{
	}
	
	GraphicsContext* OpenGLRenderer::CreateGraphicsContextImpl(Window* _window)
	{
		return new OpenGLGraphicsContext(_window);
	}

	Shader* OpenGLRenderer::CreateShaderImpl(const std::string& _vertexSrc, const std::string& _fragmentSrc)
	{
		return new OpenGLShader(_vertexSrc, _fragmentSrc);
	}

	IndexBuffer* OpenGLRenderer::CreateIndexBufferImpl(uint32_t* _indices, uint32_t _count)
	{
		return new OpenGLIndexBuffer(_indices, _count);
	}

	VertexBuffer* OpenGLRenderer::CreateVertexBufferImpl(float* _indices, uint32_t _count)
	{
		return new OpenGLVertexBuffer(_indices, _count);
	}

	VertexArray* OpenGLRenderer::CreateVertexArrayImpl()
	{
		return new OpenGLVertexArray();
	}

	void OpenGLRenderer::ClearImpl()
	{
		//::glClearColor(0.f, .63f, .56f, 1.f);
		::glClearColor(0.1f, .1f, .1f, 1.f);
		::glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderer::SetViewportImpl(std::pair<float, float> _size)
	{
		::glViewport(0, 0, _size.first, _size.second);
	}

	void OpenGLRenderer::DrawIndexedImpl(const std::shared_ptr<VertexArray>& _vertexArray)
	{
		::glDrawElements(
			GL_TRIANGLES,
			_vertexArray->GetIndexBuffer()->GetCount(),
			GL_UNSIGNED_INT,
			nullptr
		);
	}

}

