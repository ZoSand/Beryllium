#include <Beryllium/Renderer/Renderer.hpp>
#include <Beryllium/Renderer/RenderCommand.hpp>

namespace Beryllium
{
	std::unique_ptr<Renderer> Renderer::s_renderer = nullptr;
	Renderer::SceneData* Renderer::s_sceneData = new SceneData();

	void Renderer::BeginScene(const OrthographicCamera& _cam)
	{
		s_sceneData->vpMatrix = _cam.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& _array, const std::shared_ptr<Shader>& _shader)
	{
		_shader->Bind();
		_shader->SetUniform("u_ViewProjection", s_sceneData->vpMatrix);
		
		_array->Bind();
		RenderCommand::DrawIndexed(_array);
	}

	void Renderer::Submit(const Beryllium::Renderable& _renderable)
	{
		_renderable.GetShader()->Bind();
		_renderable.GetShader()->SetUniform("u_ViewProjection", s_sceneData->vpMatrix);

		_renderable.GetVertexArray()->Bind();
		RenderCommand::DrawIndexed(_renderable.GetVertexArray());
	}
	
	void Renderer::Set(Renderer* _api)
	{
		s_renderer.reset(_api);
	}

	Renderer* Renderer::Get()
	{
		return s_renderer.get();
	}
	
	GraphicsContext* Renderer::CreateGraphicsContext(Window* _window)
	{
		return s_renderer->CreateGraphicsContextImpl(_window);
	}
	
	Shader* Renderer::CreateShader(const std::string& _vertexSrc, const std::string& _fragmentSrc)
	{
		return s_renderer->CreateShaderImpl(_vertexSrc, _fragmentSrc);
	}
	
	IndexBuffer* Renderer::CreateIndexBuffer(uint32_t* _indices, uint32_t _count)
	{
		return s_renderer->CreateIndexBufferImpl(_indices, _count);
	}

	VertexBuffer* Renderer::CreateVertexBuffer(float* _indices, uint32_t _count)
	{
		return s_renderer->CreateVertexBufferImpl(_indices, _count);
	}

	VertexArray* Renderer::CreateVertexArray()
	{
		return s_renderer->CreateVertexArrayImpl();
	}

	void Renderer::Clear()
	{
		s_renderer->ClearImpl();
	}

	void Renderer::SetViewport(std::pair<float, float> _size)
	{
		s_renderer->SetViewportImpl(_size);
	}

	void Renderer::DrawIndexed(const std::shared_ptr<VertexArray>& _array)
	{
		s_renderer->DrawIndexedImpl(_array);
	}
}