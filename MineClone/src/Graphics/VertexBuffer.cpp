#include "VertexBuffer.hpp"

#include "Texture.hpp"

//VertexBuffer::VertexBuffer(PrimitiveType primitiveType) noexcept
//	: 
//	_vbo(0),
//	_vao(0),
//	_ebo(0),
//	_primitiveType(primitiveType)
//{
//}
//
//VertexBuffer::VertexBuffer(size_t size, PrimitiveType primitiveType) noexcept
//	:
//	_vbo(0),
//	_vao(0),
//	_ebo(0),
//	_primitiveType(primitiveType)
//{
//
//}

VertexBuffer::VertexBuffer(const Vertice_t* vertices, size_t size, PrimitiveType primitiveType) noexcept
	:
	_vertices(vertices, vertices + size),
	_primitiveType(primitiveType)
{
	_init();
}

//VertexBuffer::VertexBuffer(const Vertice_t* vertices, size_t verticesCount, const Indice_t* indices, size_t indicesCount, PrimitiveType primitiveType) noexcept
//	:
//	_vbo(0),
//	_vao(0),
//	_ebo(0),
//	_vertices(vertices, vertices + verticesCount),
//	_indices(indices, indices + indicesCount),
//	_primitiveType(primitiveType)
//{
//	glGenBuffers(1, &_ebo);
//}

VertexBuffer::~VertexBuffer()
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);

	if (_ebo != 0)
	{
		glDeleteBuffers(1, &_ebo);
	}
}

void VertexBuffer::create(const Vertice_t* vertices, size_t size, PrimitiveType primitiveType)
{
	_vertices = Vertices_t{ vertices, vertices + size };
	_primitiveType = primitiveType;
	_init();
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

void VertexBuffer::setTexture(Texture& texture)
{
	_texture = texture;
}

void VertexBuffer::setMatrix(const glm::mat4x4& mat)
{
	_mat = mat;
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

	if (_ebo != 0)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned), _indices.data(), GL_STATIC_DRAW);
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
