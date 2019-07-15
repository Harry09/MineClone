#include "VertexBuffer.hpp"

#include <algorithm>

#include "Texture.hpp"

VertexBuffer::VertexBuffer(size_t size, PrimitiveType primitiveType, DrawType drawType) noexcept
	: 
	_vertices(size, Vertex()),
	_primitiveType(primitiveType),
	_drawType(drawType)
{
	_init();
}

VertexBuffer::VertexBuffer(const Vertice_t* vertices, size_t size, PrimitiveType primitiveType, DrawType drawType) noexcept
	:
	_vertices(vertices, vertices + size),
	_primitiveType(primitiveType),
	_drawType(drawType)
{
	_init();
}

VertexBuffer::~VertexBuffer()
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);

	if (_ebo != 0)
	{
		glDeleteBuffers(1, &_ebo);
	}
}

void VertexBuffer::bind()
{
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
}

void VertexBuffer::unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const Vertex& VertexBuffer::getVertex(size_t index)
{
	return _vertices.at(index);
}

void VertexBuffer::setVertex(size_t index, const Vertex& vertex)
{
	_updateRange.x = std::min(_updateRange.x, index);
	_updateRange.y = std::max(_updateRange.y, index);

	_vertices.at(index) = vertex;

	_needUpdate = true;
}

Vertex& VertexBuffer::operator[](size_t index)
{
	_updateRange.x = std::min(_updateRange.x, index);
	_updateRange.y = std::max(_updateRange.y, index);

	_needUpdate = true;

	return _vertices.at(index);
}

void VertexBuffer::setTexture(Texture& texture)
{
	_texture = texture;
}

void VertexBuffer::setMatrix(const glm::mat4x4& mat)
{
	_mat = mat;
}

void VertexBuffer::update()
{
	if (_needUpdate)
	{
		bind();

		auto offset = _updateRange.x * sizeof(Vertex);
		auto size = (_updateRange.y - _updateRange.x + 1) * sizeof(Vertex);

		glBufferSubData(GL_ARRAY_BUFFER, offset, size, _vertices.data() + _updateRange.x);
		unbind();

		_needUpdate = false;
	}
}

void VertexBuffer::draw(ShaderProgram& shaderProgram)
{
	shaderProgram.setUniform("model", _mat);

	bind();
	glBindTexture(GL_TEXTURE_2D, _texture.getNativeHandle());
	glDrawArrays(static_cast<GLenum>(_primitiveType), 0, static_cast<GLsizei>(getSize()));
	unbind();
}

void VertexBuffer::_init()
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	bind();

	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertice_t), _vertices.data(), GL_STATIC_DRAW); // TODO: Add more draw type

	// TODO
	/*if (_ebo != 0)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned), _indices.data(), GL_STATIC_DRAW);
	}*/

	using posType = decltype(Vertex::position);
	using colorType = decltype(Vertex::color);
	using texCoordType = decltype(Vertex::texCoord);

	glVertexAttribPointer(0, posType::length(), GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, colorType::length(), GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(sizeof(posType)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, texCoordType::length(), GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(sizeof(posType) + sizeof(colorType)));
	glEnableVertexAttribArray(2);

	unbind();
}
