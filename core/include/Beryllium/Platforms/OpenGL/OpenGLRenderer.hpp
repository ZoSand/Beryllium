#ifndef BE_OPENGL_RENDERER_HPP
#define BE_OPENGL_RENDERER_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Renderer/Renderer.hpp>

namespace Beryllium
{
	class BE_API OpenGLRenderer : public Renderer
	{

	public:
		virtual GraphicsContext* CreateGraphicsContext(Window* _window) override;
		virtual Shader* CreateShader(const std::string& _vertexSrc, const std::string& _fragmentSrc) override;
		virtual IndexBuffer* CreateIndexBuffer(uint32_t* _indices, uint32_t _count) override;
		virtual VertexBuffer* CreateVertexBuffer(float* _indices, uint32_t _count) override;

		virtual void Clear() override;

	};
}

#endif