#include <Beryllium/Renderer/Sprite.hpp>

#include <Beryllium/Platforms/OpenGL/OpenGLShader.hpp>
#include <Beryllium/Renderer/Renderer.hpp>

namespace Beryllium
{
	Sprite::Sprite()
	{
		std::shared_ptr<Beryllium::VertexBuffer> vertexBuffer;
		std::shared_ptr<Beryllium::IndexBuffer> indexBuffer;

#pragma region data initialize
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//                                                    RENDERER            STUFF                                                     //
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*float vertices[3 * 3] = {
			-.5f, -.5f, 0.f,
			.5f, -.5f, 0.f,
			0.f, .5f, 0.f
		};
		uint32_t indices[3] = {
			0, 1, 2
		};*/
		float vertices[4 * 3] = {
			-.5f, -.5f, 0.f,
			.5f, -.5f, 0.f,
			.5f, .5f, 0.f,
			-.5f, .5f, 0.f
		};
		uint32_t indices[3 * 2] = {
			0, 1, 2,
			0, 2, 3
		};

		std::string vertexSrc = Beryllium::OpenGLShader::GetDefaultVertex();
		std::string fragmentSrc = Beryllium::OpenGLShader::GetDefaultFragment();
		//END OF TODO
#pragma endregion data initialize

		m_vertexArray.reset(Beryllium::Renderer::CreateVertexArray());

		//setting up buffer layout
		Beryllium::BufferLayout layout = {
			{ Beryllium::ShaderDataType::Float3, "i_Position" }
		};

		vertexBuffer.reset(Beryllium::Renderer::CreateVertexBuffer(vertices, sizeof(vertices) / sizeof(float)));
		vertexBuffer->SetLayout(layout);
		m_vertexArray->AddVertexBuffer(vertexBuffer);

		indexBuffer.reset(Beryllium::Renderer::CreateIndexBuffer(indices, sizeof(indices) / sizeof(uint32_t)));
		m_vertexArray->SetIndexBuffer(indexBuffer);

		m_shader.reset(Beryllium::Renderer::CreateShader(vertexSrc, fragmentSrc));
	}
}