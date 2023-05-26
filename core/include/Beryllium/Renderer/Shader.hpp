#ifndef BE_SHADER_HPP
#define BE_SHADER_HPP

#	include <Beryllium/API.hpp>

#	include <string>

namespace Beryllium
{
	class BE_API Shader 
	{
	public:
		Shader(const std::string& _vertexSrc, const std::string& _fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	
	private:
		unsigned int m_rendererId;
	};
}

#endif
