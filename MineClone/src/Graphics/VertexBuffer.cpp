#include "VertexBuffer.hpp"

#include <algorithm>

#include "ShaderProgram.hpp"

VertexBuffer::VertexBuffer(size_t size, PrimitiveType primitiveType, DrawType drawType) noexcept
	: 
	_vertices(size, Vertex()),
	_primitiveType(primitiveType),
	_drawType(drawType)
{
	init();
}

VertexBuffer::VertexBuffer(const Vertex_t* vertices, size_t size, PrimitiveType primitiveType, DrawType drawType) noexcept
	:
	_vertices(vertices, vertices + size),
	_primitiveType(primitiveType),
	_drawType(drawType)
{
	init();
}

VertexBuffer::VertexBuffer(const Vertex_t* vertices, size_t verticesCount, const Index_t* indices, size_t indicesCount, PrimitiveType primitiveType, DrawType drawType) noexcept
	: 
	_vertices(vertices, vertices + verticesCount),
	_indices(indices, indices + indicesCount),
	_primitiveType(primitiveType),
	_drawType(drawType)
{
	glGenBuffers(1, &_ebo);

	init();
}

VertexBuffer::~VertexBuffer()
{
	destroy();
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
	:
	_vbo(std::move(other._vbo)),
	_vao(std::move(other._vao)),
	_ebo(std::move(other._ebo)),
	_vertices(std::move(other._vertices)),
	_indices(std::move(other._indices)),
	_primitiveType(std::move(other._primitiveType)),
	_drawType(std::move(other._drawType)),
	_texture(std::move(other._texture)),
	_needUpdate(std::move(other._needUpdate)),
	_updateRange(std::move(other._updateRange))
{
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
	if (this != &other)
	{
		destroy();

		_vbo = std::move(other._vbo);
		_vao = std::move(other._vao);
		_ebo = std::move(other._ebo);
		_vertices = std::move(other._vertices);
		_indices = std::move(other._indices);
		_primitiveType = std::move(other._primitiveType);
		_drawType = std::move(other._drawType);
		_texture = std::move(other._texture);
		_needUpdate = std::move(other._needUpdate);
		_updateRange = std::move(other._updateRange);
	}

	return *this;
}

void VertexBuffer::bind()
{
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	if (_ebo != 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	}
}

void VertexBuffer::unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (_ebo != 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

const VertexBuffer::Vertex_t& VertexBuffer::getVertex(size_t index)
{
	return _vertices[index];
}

void VertexBuffer::setVertex(size_t index, const Vertex_t& vertex)
{
	_updateRange.x = std::min(_updateRange.x, index);
	_updateRange.y = std::max(_updateRange.y, index);

	_vertices[index] = vertex;

	_needUpdate = true;
}

void VertexBuffer::setVertices(size_t offset, const Vertex_t* start, size_t size)
{
	_updateRange.x = std::min(_updateRange.x, offset);
	_updateRange.y = std::max(_updateRange.y, offset + size) - 1;

	std::copy(start, start + size, _vertices.begin() + offset);

	_needUpdate = true;
}

VertexBuffer::Vertex_t& VertexBuffer::operator[](size_t index)
{
	_updateRange.x = std::min(_updateRange.x, index);
	_updateRange.y = std::max(_updateRange.y, index);

	_needUpdate = true;

	return _vertices[index];
}

void VertexBuffer::setTexture(Texture& texture)
{
	_texture = texture;
}

void VertexBuffer::resize(size_t size)
{
	if (getSize() != size)
	{
		_needUpdate = true;
		_needReallocate = _vertices.size() < size;

		_updateRange = { 0, size - 1 };

		_vertices.resize(size);
	}
}

void VertexBuffer::update()
{
	if (_needUpdate)
	{
		bind();

		if (_needReallocate)
		{
			glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex_t), _vertices.data(), _drawType);

			_needReallocate = false;
		}
		else
		{
			auto offset = _updateRange.x * sizeof(Vertex);
			auto size = (_updateRange.y - _updateRange.x + 1) * sizeof(Vertex);

			glBufferSubData(GL_ARRAY_BUFFER, offset, size, _vertices.data() + _updateRange.x);
		}

		_updateRange = { -1, 0 };
		
		_needUpdate = false;
		unbind();
	}
}

void VertexBuffer::draw(ShaderProgram& shaderProgram)
{
	update();

	shaderProgram.setUniform("model", _matrix);

	bind();

	auto _textureNativeHandle = _texture.getNativeHandle();

	if (_textureNativeHandle != 0)
	{
		glBindTexture(GL_TEXTURE_2D, _textureNativeHandle);
	}

	if (_ebo != 0)
	{
		glDrawElements(static_cast<GLenum>(_primitiveType), static_cast<GLsizei>(_indices.size()), GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(static_cast<GLenum>(_primitiveType), 0, static_cast<GLsizei>(getSize()));
	}
	unbind();
}

void VertexBuffer::init()
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	bind();

	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex_t), _vertices.data(), _drawType);

	if (_ebo != 0)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(Indices_t), _indices.data(), _drawType);
	}

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

void VertexBuffer::destroy()
{
	_vertices.clear();

	glDeleteVertexArrays(1, &_vao);
	_vao = 0;

	glDeleteBuffers(1, &_vbo);
	_vbo = 0;

	if (_ebo != 0)
	{
		glDeleteBuffers(1, &_ebo);
	}

	_updateRange = { -1, 0 };

	_needUpdate = false;
}
