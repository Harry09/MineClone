#include "Block.hpp"

#include <glm/gtc/matrix_transform.hpp>

Block::Block()
	: 
	_texture("textures.jpg")
{
	auto vertices = {
		Vertex { glm::vec3 { -0.5f, -0.5f, 0.f }, glm::vec2 { 0.f, 0.f } },
		Vertex { glm::vec3 {  0.5f, -0.5f, 0.f }, glm::vec2 { 16.f / 256.f, 0.f } },
		Vertex { glm::vec3 {  0.5f,  0.5f, 0.f }, glm::vec2 { 16.f / 256.f, 16.f / 256.f } },
		Vertex { glm::vec3 { -0.5f,  0.5f, 0.f }, glm::vec2 { 0.f, 16.f / 256.f } }
	};

	_vertexBuffer.create(vertices.begin(), vertices.size(), PrimitiveType::TriangleFan);

	_vertexBuffer.setTexture(_texture);
	auto mat = _vertexBuffer.getMatrix();
	mat = glm::translate(mat, {0.0f, 0.f, 0.f});
	_vertexBuffer.setMatrix(mat);

}

void Block::draw(ShaderProgram& shader)
{
	_vertexBuffer.draw(shader);
}
