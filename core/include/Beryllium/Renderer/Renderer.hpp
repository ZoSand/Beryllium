#ifndef BE_RENDERER_HPP
#define BE_RENDERER_HPP

#	include <Beryllium/API.hpp>

#	include <Beryllium/Window.hpp>

#	include <Beryllium/Renderer/GraphicsContext.hpp>
#	include <Beryllium/Renderer/IndexBuffer.hpp>
#	include <Beryllium/Renderer/Shader.hpp>
#	include <Beryllium/Renderer/VertexBuffer.hpp>
#	include <Beryllium/Renderer/VertexArray.hpp>

#	include <memory>

namespace Beryllium
{
	class BE_API Renderer
	{
	public:
		static void Set(Renderer* _api);
		static Renderer* Get();

		static GraphicsContext* CreateGraphicsContext(Window* _window);
		static Shader* CreateShader(const std::string& _vertexSrc, const std::string& _fragmentSrc);
		static IndexBuffer* CreateIndexBuffer(uint32_t* _indices, uint32_t _count);
		static VertexBuffer* CreateVertexBuffer(float* _indices, uint32_t _count);
		static VertexArray* CreateVertexArray();
		
		static void Clear();
		static void SetViewport(std::pair<float, float> _size);
		
	protected:
		virtual GraphicsContext* CreateGraphicsContextImpl(Window* _window) = 0;
		virtual Shader* CreateShaderImpl(const std::string& _vertexSrc, const std::string& _fragmentSrc) = 0;
		virtual IndexBuffer* CreateIndexBufferImpl(uint32_t* _indices, uint32_t _count) = 0;
		virtual VertexBuffer* CreateVertexBufferImpl(float* _indices, uint32_t _count) = 0;
		virtual VertexArray* CreateVertexArrayImpl() = 0;

		virtual void ClearImpl() = 0;
		virtual void SetViewportImpl(std::pair<float, float> _size) = 0;

	private:
		static std::unique_ptr<Renderer> s_renderer;

	};

}

#endif