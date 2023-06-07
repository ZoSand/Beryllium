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

		void SetUniform(const std::string& _name, const glm::mat4& _mat) override;

		static std::string GetDefaultFragment()
		{
			return R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;
			in vec3 t_Position;

			vec4 remap(vec4 _val, vec2 _min, vec2 _max)
			{
				return _max.x + (_val - _min.x) * (_max.y -  _max.x) / (_min.y - _min.x);
			}

			void main()
			{
				o_Color = vec4(0.9, 0.9, 0.9, 0.5);
				//o_Color = remap(vec4(t_Position, 0.5), vec2(-1, 1), vec2(0, 1));
			}
			)";
		};
		static std::string GetDefaultVertex()
		{
			return R"(
			#version 330 core

			layout(location = 0) in vec3 i_Position;

			uniform mat4 u_ViewProjection;

			out vec3 t_Position;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(i_Position, 1.0);
				t_Position = i_Position; 
			}
			)";
		};
	};
}

#endif