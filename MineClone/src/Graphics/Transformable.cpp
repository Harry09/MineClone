#include "Transformable.hpp"

#include <glm/gtc/matrix_transform.hpp>

void Transformable::setPos(const glm::vec3& pos)
{
	_pos = pos;
	_needUpdate = true;
}

const glm::vec3& Transformable::getPos() const
{
	return _pos;
}

void Transformable::move(const glm::vec3& offset)
{
	_pos += offset;
	_needUpdate = true;
}

void Transformable::setScale(const glm::vec3& scale)
{
	_scale = scale;
	_needUpdate = true;
}

const glm::vec3& Transformable::getScale() const
{
	return _scale;
}

void Transformable::scale(const glm::vec3& scale)
{
	_scale *= scale;
	_needUpdate = true;
}

void Transformable::setRotation(const glm::vec3& rotation)
{
	_rotation = rotation;
	_needUpdate = true;
}

const glm::vec3& Transformable::getRotation() const
{
	return _rotation;
}

void Transformable::rotate(const glm::vec3& rotation)
{
	_rotation += rotation;
	_needUpdate = true;
}

void Transformable::setMatrix(const glm::mat4& matrix)
{
	_matrix = matrix;
}

glm::mat4 Transformable::getMatrix()
{
	updateMatrix();

	return _matrix;
}

void Transformable::updateMatrix()
{
	if (_needUpdate)
	{
		_matrix = glm::mat4{ 1.f };
		
		_matrix = glm::translate(_matrix, _pos);
		_matrix = glm::scale(_matrix, _scale);
		_matrix = glm::rotate(_matrix, _rotation.x, { 1.f, 0.f, 0.f });
		_matrix = glm::rotate(_matrix, _rotation.y, { 0.f, 1.f, 0.f });
		_matrix = glm::rotate(_matrix, _rotation.z, { 0.f, 0.f, 1.f });

		_needUpdate = false;
	}
}
