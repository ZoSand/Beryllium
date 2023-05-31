#include <Beryllium/Platforms/OpenGL/OpenGLRenderer.hpp>
#include <Beryllium/Platforms/OpenGL/OpenGLContext.hpp>
#include <Beryllium/Platforms/OpenGL/OpenGLIndexBuffer.hpp>
#include <Beryllium/Platforms/OpenGL/OpenGLShader.hpp>
#include <Beryllium/Platforms/OpenGL/OpenGLVertexBuffer.hpp>

#include <glad/glad.h>

namespace Beryllium
{
	GraphicsContext* OpenGLRenderer::CreateGraphicsContext(Window* _window)
	{
		return new OpenGLContext(_window);
	}

	Shader* OpenGLRenderer::CreateShader(const std::string& _vertexSrc, const std::string& _fragmentSrc)
	{
		return new OpenGLShader(_vertexSrc, _fragmentSrc);
	}

	IndexBuffer* OpenGLRenderer::CreateIndexBuffer(uint32_t* _indices, uint32_t _count)
	{
		return new OpenGLIndexBuffer(_indices, _count);
	}

	VertexBuffer* OpenGLRenderer::CreateVertexBuffer(float* _indices, uint32_t _count)
	{
		return new OpenGLVertexBuffer(_indices, _count);
	}

	void OpenGLRenderer::Clear()
	{
		::glClearColor(0.f, .63f, .56f, 1.f);
		::glClear(GL_COLOR_BUFFER_BIT);
	}

}

