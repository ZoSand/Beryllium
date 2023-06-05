#include <Beryllium/Renderer/OrthographicCamera.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace Beryllium
{
	OrthographicCamera::OrthographicCamera(float _left, float _right, float _bottom, float _top)
		: m_projectionMatrix(glm::ortho(_left, _right, _bottom, _top, -1.f, 1.f))
		, m_viewMatrix(1.f)
	{
		m_ViewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void OrthographicCamera::SetPosition(const glm::vec3& _pos)
	{
		m_position = _pos;
		UpdateViewMatrix();
	}

	const glm::vec3& OrthographicCamera::GetPosition() const
	{
		return m_position;
	}

	void OrthographicCamera::Translate(const glm::vec3& _trans)
	{
		SetPosition(m_position + _trans);
	}

	void OrthographicCamera::SetRotation(float _zRotation)
	{
		m_zRotation = _zRotation;
		UpdateViewMatrix();
	}

	float OrthographicCamera::GetRotation() const
	{
		return m_zRotation;
	}

	const glm::mat4& OrthographicCamera::GetProjectionMatrix() const
	{
		return m_projectionMatrix;
	}

	const glm::mat4& OrthographicCamera::GetViewMatrix() const
	{
		return m_viewMatrix;
	}

	const glm::mat4& OrthographicCamera::GetViewProjectionMatrix() const
	{
		return m_ViewProjectionMatrix;
	}

	void OrthographicCamera::SetProjection(float _left, float _right, float _bottom, float _top)
	{
		m_projectionMatrix = glm::ortho(_left, _right, _bottom, _top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void OrthographicCamera::UpdateViewMatrix()
	{
		glm::mat4 transformation
			= glm::translate(glm::mat4(1.f), m_position) 
			* glm::rotate(glm::mat4(1.f), m_zRotation, glm::vec3(0, 0, 1));

		m_viewMatrix = glm::inverse(transformation);
		m_ViewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}
}