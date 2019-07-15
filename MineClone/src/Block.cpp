#include "Block.hpp"

#include <glm/gtc/matrix_transform.hpp>

Block::Block()
	:
	_texture("textures.jpg")
{
	_vertexBuffer[0] = { glm::vec3 { -0.5f, -0.5f, 0.f }, glm::vec2 { 0.f, 0.f } };
	_vertexBuffer[1] = { glm::vec3 { 0.5f, -0.5f, 0.f }, glm::vec2{ 16.f / 256.f, 0.f } };
	_vertexBuffer[2] = { glm::vec3 {  0.5f,  0.5f, 0.f }, glm::vec2 { 16.f / 256.f, 16.f / 256.f } };
	_vertexBuffer[3] = { glm::vec3 { -0.5f,  0.5f, 0.f }, glm::vec2 { 0.f, 16.f / 256.f } };
	_vertexBuffer.update();

	_vertexBuffer.setTexture(_texture);
}

void Block::draw(ShaderProgram& shader)
{
	_vertexBuffer.draw(shader);
}

void Block::update()
{
	_vertexBuffer[0].texCoord = glm::vec2{ 16.f / 256.f, 0 };
	_vertexBuffer[1].texCoord = glm::vec2{ 32.f / 256.f, 0 };
	_vertexBuffer[2].texCoord = glm::vec2{ 32.f / 256.f, 16.f / 256.f };
	_vertexBuffer[3].texCoord = glm::vec2{ 16.f / 256.f, 16.f / 256.f };

	_vertexBuffer.update();
}
