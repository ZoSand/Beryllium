#ifndef BE_ORTHOGRAPHIC_CAMERA_HPP
#define BE_ORTHOGRAPHIC_CAMERA_HPP

#include <Beryllium/API.hpp>
#include <glm/glm.hpp>

namespace Beryllium
{
	class BE_API OrthographicCamera
	{
	public:
		OrthographicCamera(float _left = -1.f, float _right = 1.f, float _bottom = -1.f, float _top = 1.f);

		void SetPosition(const glm::vec3& _pos);
		const glm::vec3& GetPosition() const;
		void Translate(const glm::vec3& _trans);

		void SetRotation(float _zRotation);
		float GetRotation() const;

		const glm::mat4& GetProjectionMatrix() const;
		const glm::mat4& GetViewMatrix() const;
		const glm::mat4& GetViewProjectionMatrix() const;

		void SetProjection(float _left, float _right, float _bottom, float _top);

	private:
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_position = { 0.f ,  0.f ,  0.f };
		float m_zRotation = 0;

		void UpdateViewMatrix();
	};
}

#endif