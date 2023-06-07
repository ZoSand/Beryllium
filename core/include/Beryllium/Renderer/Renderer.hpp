#ifndef BE_RENDERER_HPP
#define BE_RENDERER_HPP

#	include <Beryllium/API.hpp>

#	include <Beryllium/Window.hpp>

#	include <Beryllium/Renderer/GraphicsContext.hpp>
#	include <Beryllium/Renderer/IndexBuffer.hpp>
#	include <Beryllium/Renderer/Shader.hpp>
#	include <Beryllium/Renderer/VertexBuffer.hpp>
#	include <Beryllium/Renderer/VertexArray.hpp>
#	include <Beryllium/Renderer/OrthographicCamera.hpp>
#	include <Beryllium/Renderer/Renderable.hpp>

#	include <memory>

namespace Beryllium
{
	class BE_API Renderer
	{
	public:
		//commands
		static void BeginScene(const OrthographicCamera& _cam);
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& _array, const std::shared_ptr<Shader>& _shader);
		static void Submit(const Beryllium::Renderable& _renderable);

		//misc
		static void Set(Renderer* _api);
		static Renderer* Get();

		static GraphicsContext* CreateGraphicsContext(Window* _window);
		static Shader* CreateShader(const std::string& _vertexSrc, const std::string& _fragmentSrc);
		static IndexBuffer* CreateIndexBuffer(uint32_t* _indices, uint32_t _count);
		static VertexBuffer* CreateVertexBuffer(float* _indices, uint32_t _count);
		static VertexArray* CreateVertexArray();
		
		static void Clear();
		static void SetViewport(std::pair<float, float> _size);
		
		static void DrawIndexed(const std::shared_ptr<VertexArray>& _array);

	protected:
		virtual GraphicsContext* CreateGraphicsContextImpl(Window* _window) = 0;
		virtual Shader* CreateShaderImpl(const std::string& _vertexSrc, const std::string& _fragmentSrc) = 0;
		virtual IndexBuffer* CreateIndexBufferImpl(uint32_t* _indices, uint32_t _count) = 0;
		virtual VertexBuffer* CreateVertexBufferImpl(float* _indices, uint32_t _count) = 0;
		virtual VertexArray* CreateVertexArrayImpl() = 0;

		//TODO: clear color
		virtual void ClearImpl() = 0;
		virtual void SetViewportImpl(std::pair<float, float> _size) = 0;

		virtual void DrawIndexedImpl(const std::shared_ptr<VertexArray>& _array) = 0;

	private:
		static std::unique_ptr<Renderer> s_renderer;

		struct SceneData
		{
			glm::mat4 vpMatrix;
		};

		static SceneData* s_sceneData;

	};

}

#endif