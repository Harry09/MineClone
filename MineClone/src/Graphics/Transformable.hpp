#pragma once

#include <glm/mat4x4.hpp>

class Transformable
{
protected:
	glm::mat4 _matrix = {
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	};

	glm::vec3 _scale{ 1.f };
	glm::vec3 _pos{ 0.f };
	glm::vec3 _rotation{ 0.f };

public:
	void setPos(const glm::vec3& pos);
	const glm::vec3& getPos() const;

	void move(const glm::vec3& offset);

	void setScale(const glm::vec3& scale);
	const glm::vec3& getScale() const;

	void scale(const glm::vec3& scale);

	void rotate(float angle, const glm::vec3& rotation);
	const glm::vec3& getRotation() const;

	void setMatrix(const glm::mat4& matrix);
	glm::mat4 getMatrix() const;
};
