#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Ray
{
private:
	const glm::vec3& _start;
	glm::vec3 _end;

	glm::vec2 _direction;

public:
	Ray(const glm::vec3& pos, const glm::vec2& dir);

	void step(float scale);

	const auto& getStart() const { return _start; }
	const auto& getEnd() const { return _end; }

	float length() const;
};