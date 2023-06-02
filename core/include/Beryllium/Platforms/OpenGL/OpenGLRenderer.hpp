#ifndef BE_OPENGL_RENDERER_HPP
#define BE_OPENGL_RENDERER_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Renderer/Renderer.hpp>

namespace Beryllium
{
	class BE_API OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer();
	protected:
		virtual GraphicsContext* CreateGraphicsContextImpl(Window* _window) override;
		virtual Shader* CreateShaderImpl(const std::string& _vertexSrc, const std::string& _fragmentSrc) override;
		virtual IndexBuffer* CreateIndexBufferImpl(uint32_t* _indices, uint32_t _count) override;
		virtual VertexBuffer* CreateVertexBufferImpl(float* _indices, uint32_t _count) override;
		virtual VertexArray* CreateVertexArrayImpl() override;

		virtual void ClearImpl() override;
		virtual void SetViewportImpl(std::pair<float, float> _size) override;

		virtual void DrawIndexedImpl(const std::shared_ptr<VertexArray>& _vertexArray) override;
	};
}

#endif