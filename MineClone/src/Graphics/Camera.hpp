#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
public:
	enum Mode
	{
		Target,
		Rotation
	};

private:
	glm::vec3 _position{ 0.f, 0.f, 0.f };
	glm::vec3 _target{ 0.f, 0.f, 0.f };
	glm::vec2 _rotation{ -90.f, 0.f };

	Mode _mode = Mode::Rotation;

	glm::mat4 _viewMatrix{ 1.f };
	glm::mat4 _projectionMatrix{ 1.f };

	float _fov = 45.f;

	float _aspectRatio = 0.f;

	bool _viewNeedUpdate = true;
	bool _projectionNeedUpdate = true;

public:
	Camera() = default;
	~Camera() = default;

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix(const glm::vec2& targetSize);

	void setAspectRatio(float aspect) { _aspectRatio = aspect; _projectionNeedUpdate = true; }

	void setFOV(float fov) { _fov = fov; _projectionNeedUpdate = true; }
	float getFOV() const { return _fov; }

	void setMode(Mode mode) { _mode = mode; _viewNeedUpdate = true; }
	Mode getMode() const { return _mode; }

	void setPosition(const glm::vec3& position) { _position = position; _viewNeedUpdate = true; }
	const glm::vec3& getPosition() const { return _position; }

	void move(const glm::vec3& offset) { _position += offset; _viewNeedUpdate = true; }

	void setTargetPosition(const glm::vec3& targetPosition) { _target = targetPosition; _viewNeedUpdate = true; }
	const glm::vec3& getTargetPosition() const { return _target; }

	void moveTagetPosition(const glm::vec3& offset) { _target += offset; _viewNeedUpdate = true; }

	void setRotation(const glm::vec2& rotation) { _rotation = rotation; _viewNeedUpdate = true; }
	const glm::vec2& getRotation() const { return _rotation; }

	void rotate(const glm::vec2& value) { _rotation += value; _viewNeedUpdate = true; }
};

