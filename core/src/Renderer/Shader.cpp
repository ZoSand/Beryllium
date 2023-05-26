#include <Beryllium/Renderer/Shader.hpp>
#include <Beryllium/Logger.hpp>

#include <glad/glad.h>
#include <vector>

namespace Beryllium
{
	Shader::Shader(const std::string& _vertexSrc, const std::string& _fragmentSrc)
	{
		::GLuint vertexShader;
		::GLuint fragmentShader;
		::GLint isCompiled = 0;
		::GLint isLinked = 0;

		// Create an empty vertex shader handle
		vertexShader = ::glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const ::GLchar* source = _vertexSrc.c_str();
		::glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		::glCompileShader(vertexShader);
		::glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			::GLint maxLength = 0;
			::glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<::GLchar> infoLog(maxLength);
			::glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			::glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			BE_CRITICAL("[OpenGL][Shader] Vertex shader compilation failed!");
			BE_CRITICAL("%s", infoLog.data());

			//TODO: ASSERT WITH BE_ASSERT
			throw std::runtime_error("Vertex shader compilation failed!");
		}

		// Create an empty fragment shader handle
		fragmentShader = ::glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = _fragmentSrc.c_str();
		::glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		::glCompileShader(fragmentShader);

		::glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			::GLint maxLength = 0;
			::glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<::GLchar> infoLog(maxLength);
			::glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			::glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			::glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			BE_CRITICAL("[OpenGL][Shader] Fragment shader compilation failed!");
			BE_CRITICAL("%s", infoLog.data());

			//TODO: ASSERT WITH BE_ASSERT
			throw std::runtime_error("Vertex shader compilation failed!");
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_rendererId = ::glCreateProgram();

		// Attach our shaders to our program
		::glAttachShader(m_rendererId, vertexShader);
		::glAttachShader(m_rendererId, fragmentShader);

		// Link our program
		::glLinkProgram(m_rendererId);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		::glGetProgramiv(m_rendererId, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			::GLint maxLength = 0;
			::glGetProgramiv(m_rendererId, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<::GLchar> infoLog(maxLength);
			::glGetProgramInfoLog(m_rendererId, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			::glDeleteProgram(m_rendererId);
			// Don't leak shaders either.
			::glDeleteShader(vertexShader);
			::glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			BE_CRITICAL("[OpenGL][Shader] Program linkage failed!");
			BE_CRITICAL("%s", infoLog.data());

			//TODO: ASSERT WITH BE_ASSERT
			throw std::runtime_error("Vertex shader compilation failed!");
		}

		// Always detach shaders after a successful link.
		::glDetachShader(m_rendererId, vertexShader);
		::glDetachShader(m_rendererId, fragmentShader);

		BE_TRACE("[OpenGL][Shader] Shader {%u} compiled and linked successfully", m_rendererId);
	}

	Shader::~Shader()
	{
		::glDeleteProgram(m_rendererId);
	}

	void Shader::Bind() const
	{
		::glUseProgram(m_rendererId);
	}

	void Shader::Unbind() const
	{
		::glUseProgram(0);
	}
}