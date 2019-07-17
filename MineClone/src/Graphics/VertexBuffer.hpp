#pragma once

#include <vector>
#include <memory>

#include <glm/mat4x4.hpp>

#include "Vertex.hpp"
#include "PrimitiveType.hpp"
#include "Texture.hpp"
#include "ShaderProgram.hpp"

class VertexBuffer
{
public:
	enum DrawType
	{
		Static = GL_STATIC_DRAW,
		Dynamic = GL_DYNAMIC_DRAW,
		Stream = GL_STREAM_DRAW
	};

private:
	using Vertex_t = Vertex;
	using Vertices_t = std::vector<Vertex_t>;
	using Index_t = unsigned;
	using Indices_t = std::vector<Index_t>;
	using ullvec2 = glm::vec<2, size_t, glm::defaultp>;

private:
	unsigned _vbo = 0;
	unsigned _vao = 0;
	unsigned _ebo = 0;

	Vertices_t _vertices;
	Indices_t _indices;

	PrimitiveType _primitiveType = PrimitiveType::Triangles;
	DrawType _drawType = DrawType::Static;

	Texture _texture;

	bool _needUpdate = false;
	ullvec2 _updateRange{ -1, 0 };

	glm::mat4x4 _mat = 
						{ 
							1.f, 0.f, 0.f, 0.f,
							0.f, 1.f, 0.f, 0.f,
							0.f, 0.f, 1.f, 0.f,
							0.f, 0.f, 0.f, 1.f
						};

public:
	VertexBuffer() noexcept = default;
	VertexBuffer(size_t size, PrimitiveType primitiveType, DrawType drawType = DrawType::Static) noexcept;
	VertexBuffer(const Vertex_t* vertices, size_t size, PrimitiveType primitiveType, DrawType drawType = DrawType::Static) noexcept;
	VertexBuffer(const Vertex_t* vertices, size_t verticesCount, const Index_t* indices, size_t indicesCount, PrimitiveType primitiveType, DrawType drawType = DrawType::Static) noexcept;
	~VertexBuffer();

	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer& operator=(const VertexBuffer&) = delete;

	VertexBuffer(VertexBuffer&& other) noexcept;
	VertexBuffer& operator=(VertexBuffer&& other) noexcept;

	void bind();
	void unbind();

	const Vertex& getVertex(size_t index);
	void setVertex(size_t index, const Vertex& vertex);

	Vertex& operator[](size_t index);

	void setTexture(Texture& texture);
	void setMatrix(const glm::mat4x4& mat);
	const glm::mat4x4& getMatrix() const { return _mat; }

	PrimitiveType getPrimitiveType() const { return _primitiveType; }
	size_t getSize() const { return _vertices.size(); }

	void update();
	void draw(ShaderProgram& shaderProgram);

private:
	void init();
	void destroy();
};