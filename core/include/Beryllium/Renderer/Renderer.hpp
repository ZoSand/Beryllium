#ifndef BE_RENDERER_HPP
#define BE_RENDERER_HPP

#	include <Beryllium/API.hpp>

#	include <Beryllium/Window.hpp>

#	include <Beryllium/Renderer/GraphicsContext.hpp>
#	include <Beryllium/Renderer/IndexBuffer.hpp>
#	include <Beryllium/Renderer/Shader.hpp>
#	include <Beryllium/Renderer/VertexBuffer.hpp>

#	include <memory>

namespace Beryllium
{
	class BE_API Renderer
	{
	public:
		static void Set(Renderer* _api);
		static Renderer* Get();

		virtual GraphicsContext* CreateGraphicsContext(Window* _window) = 0;
		virtual Shader* CreateShader(const std::string& _vertexSrc, const std::string& _fragmentSrc) = 0;
		virtual IndexBuffer* CreateIndexBuffer(uint32_t* _indices, uint32_t _count) = 0;
		virtual VertexBuffer* CreateVertexBuffer(float* _indices, uint32_t _count) = 0;

		virtual void Clear() = 0;

	private:
		static std::unique_ptr<Renderer> s_renderer;

	};

}

#endif