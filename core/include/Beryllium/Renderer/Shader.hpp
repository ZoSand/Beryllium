#ifndef BE_SHADER_HPP
#define BE_SHADER_HPP

#	include <Beryllium/API.hpp>

#include <glm/glm.hpp>

#	include <string>

namespace Beryllium
{
	class BE_API Shader 
	{
	public:
		virtual ~Shader();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetUniform(const std::string& _name, const glm::mat4& _mat) = 0;

	protected:
		unsigned int m_rendererId;
	};
}

#endif
