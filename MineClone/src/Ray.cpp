#include "Ray.hpp"

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>

Ray::Ray(const glm::vec3& pos, const glm::vec2& dir)
	: _start(pos), _end(pos), _direction(glm::radians(dir))
{

}

void Ray::step(float scale)
{
	_end.x += cos(_direction.x) * scale;
	_end.y += tan(_direction.y) * scale;
	_end.z += sin(_direction.x) * scale;
}

float Ray::length() const
{
	return glm::distance(_start, _end);
}
