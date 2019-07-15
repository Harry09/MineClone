#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::getViewMatrix()
{
	if (_viewNeedUpdate)
	{
		switch (_mode)
		{
			case Mode::Target:
			{
			} break;
			case Mode::Rotation:
			{
				_target.x = cos(glm::radians(_rotation.x)) * cos(glm::radians(_rotation.y));
				_target.y = sin(glm::radians(_rotation.y));
				_target.z = sin(glm::radians(_rotation.x)) * cos(glm::radians(_rotation.y));

				_target += _position;
			} break;
		}

		_viewMatrix = glm::lookAt(_position, _target, glm::vec3{ 0.f, 1.f, 0.f });

		_viewNeedUpdate = false;
	}

	return _viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix(const glm::vec2& targetSize)
{
	if (_projectionNeedUpdate)
	{
		_projectionMatrix = glm::perspective(glm::radians(_fov), targetSize.x / targetSize.y, 0.1f, 100.0f);

		_projectionNeedUpdate = false;
	}

	return _projectionMatrix;
}