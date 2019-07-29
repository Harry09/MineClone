#include "Transformable.hpp"

#include <glm/gtc/matrix_transform.hpp>

void Transformable::setPos(const glm::vec3& pos)
{
	_matrix = glm::translate(_matrix, pos - _pos);
	_pos = pos;
}

const glm::vec3& Transformable::getPos() const
{
	return _pos;
}

void Transformable::move(const glm::vec3& offset)
{
	_matrix = glm::translate(_matrix, offset);
	_pos += offset;
}

void Transformable::setScale(const glm::vec3& scale)
{
	_matrix = glm::scale(_matrix, _scale - scale);
	_scale = scale;
}

const glm::vec3& Transformable::getScale() const
{
	return _scale;
}

void Transformable::scale(const glm::vec3& scale)
{
	_matrix = glm::scale(_matrix, scale);
	_scale += scale;
}

void Transformable::rotate(float angle, const glm::vec3& rotation)
{
	_matrix = glm::rotate(_matrix, angle, rotation);
	_rotation += angle * rotation;
}

const glm::vec3& Transformable::getRotation() const
{
	return _rotation;
}

void Transformable::setMatrix(const glm::mat4& matrix)
{
	_matrix = matrix;
}

glm::mat4 Transformable::getMatrix() const
{
	return _matrix;
}
