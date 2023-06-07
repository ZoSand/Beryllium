#ifndef BE_RENDERABLE_HPP
#define BE_RENDERABLE_HPP

#	include <Beryllium/API.hpp>

#	include <Beryllium/Renderer/VertexArray.hpp>
#	include <Beryllium/Renderer/Shader.hpp>

#	include <memory>

namespace Beryllium
{
	class BE_API Renderable
	{
	public:
		virtual const std::shared_ptr<Beryllium::VertexArray>& GetVertexArray() const;
		virtual const std::shared_ptr<Beryllium::Shader>& GetShader() const;
	
	protected:
		virtual void SetVertexArray(std::shared_ptr<Beryllium::VertexArray> _array);
		virtual void SetShader(std::shared_ptr<Beryllium::Shader> _shader);

	protected:
		std::shared_ptr<Beryllium::VertexArray> m_vertexArray;
		std::shared_ptr<Beryllium::Shader> m_shader;
	};
}

#endif // ifndef BE_RENDERABLE_HPP
