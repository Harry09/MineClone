#pragma once

#include <vector>
#include <memory>

#include <glm/mat4x4.hpp>

#include "Vertex.hpp"
#include "PrimitiveType.hpp"
#include "Texture.hpp"
#include "Transformable.hpp"

class ShaderProgram;

class VertexBuffer : public Transformable
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
	bool _needReallocate = false;
	ullvec2 _updateRange{ -1, 0 };

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

	const Vertex_t& getVertex(size_t index);
	void setVertex(size_t index, const Vertex_t& vertex);
	void setVertices(size_t offset, const Vertex_t* start, size_t size);

	Vertex_t& operator[](size_t index);

	void setTexture(Texture& texture);

	PrimitiveType getPrimitiveType() const { return _primitiveType; }

	void resize(size_t size);
	size_t getSize() const { return _vertices.size(); }

	void update();
	void draw(ShaderProgram& shaderProgram);

private:
	void init();
	void destroy();
};