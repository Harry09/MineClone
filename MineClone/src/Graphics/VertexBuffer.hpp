﻿#pragma once

#include <vector>
#include <memory>

#include <glm/mat4x4.hpp>

#include "Vertex.hpp"
#include "PrimitiveType.hpp"
#include "Texture.hpp"
#include "RenderState.hpp"

class VertexBuffer
{
private:
	using Vertice_t = Vertex;
	using Vertices_t = std::vector<Vertice_t>;
	using Indice_t = unsigned;
	using Indices_t = std::vector<Indice_t>;

private:
	unsigned _vbo = 0;
	unsigned _vao = 0;
	unsigned _ebo = 0;

	Vertices_t _vertices;
	Indices_t _indices;

	PrimitiveType _primitiveType = PrimitiveType::Triangles;

	Texture _texture;

	glm::mat4x4 _mat = 
						{ 
							1.f, 0.f, 0.f, 0.f,
							0.f, 1.f, 0.f, 0.f,
							0.f, 0.f, 1.f, 0.f,
							0.f, 0.f, 0.f, 1.f
						};

public:
	VertexBuffer() = default;
	//VertexBuffer(PrimitiveType primitiveType) noexcept;
	//VertexBuffer(size_t size, PrimitiveType primitiveType) noexcept;
	VertexBuffer(const Vertice_t* vertices, size_t size, PrimitiveType primitiveType) noexcept;
	//VertexBuffer(const Vertice_t* vertices, size_t verticesCount, const Indice_t* indices, size_t indicesCount, PrimitiveType primitiveType) noexcept;

	~VertexBuffer();

	void create(const Vertice_t* vertices, size_t size, PrimitiveType primitiveType);

	void bind();
	void unbind();

	void setTexture(Texture& texture);
	void setMatrix(const glm::mat4x4& mat);
	const glm::mat4x4& getMatrix() const { return _mat; }

	PrimitiveType getPrimitiveType() const { return _primitiveType; }
	size_t getSize() const { return _vertices.size(); }

	void draw(ShaderProgram& shaderProgram);

private:
	void _init();
};