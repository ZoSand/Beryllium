#include <Beryllium/Renderer/Renderable.hpp>

namespace Beryllium
{
	const std::shared_ptr<Beryllium::VertexArray>& Renderable::GetVertexArray() const
	{
		return m_vertexArray;
	}

	const std::shared_ptr<Beryllium::Shader>& Renderable::GetShader() const
	{
		return m_shader;
	}

	void Renderable::SetVertexArray(std::shared_ptr<Beryllium::VertexArray> _array)
	{
		m_vertexArray = _array;
	}

	void Renderable::SetShader(std::shared_ptr<Beryllium::Shader> _shader)
	{
		m_shader = _shader;
	}	
}