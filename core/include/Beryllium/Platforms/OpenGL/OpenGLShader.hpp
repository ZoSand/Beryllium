#ifndef BE_OPENGL_SHADER_HPP
#define BE_OPENGL_SHADER_HPP

#	include <Beryllium/API.hpp>
#	include <Beryllium/Renderer/Shader.hpp>

#	include <string.h>

namespace Beryllium
{
	class BE_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& _vertexSrc, const std::string& _fragmentSrc);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;
	};
}

#endif