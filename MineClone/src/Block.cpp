#include "Block.hpp"

#include <glm/gtc/matrix_transform.hpp>

Block::Block()
	:
	_texture("textures.jpg"),
	_textureMap(_texture, 16)
{
	_vertexBuffer[0] = { glm::vec3 { -0.5f, -0.5f, 0.f }, _textureMap.getTextureCoords(Textures::Dirt, TextureMap::LeftBottom) };
	_vertexBuffer[1] = { glm::vec3 {  0.5f, -0.5f, 0.f }, _textureMap.getTextureCoords(Textures::Dirt, TextureMap::RightBottom) };
	_vertexBuffer[2] = { glm::vec3 {  0.5f,  0.5f, 0.f }, _textureMap.getTextureCoords(Textures::Dirt, TextureMap::RightTop) };
	_vertexBuffer[3] = { glm::vec3 { -0.5f,  0.5f, 0.f }, _textureMap.getTextureCoords(Textures::Dirt, TextureMap::LeftTop) };

	_vertexBuffer.update();

	_vertexBuffer.setTexture(_texture);
}

void Block::draw(ShaderProgram& shader)
{
	_vertexBuffer.draw(shader);
}

void Block::update()
{
	_vertexBuffer[0].texCoord = _textureMap.getTextureCoords(Textures::GrassSide, TextureMap::LeftBottom);
	_vertexBuffer[1].texCoord = _textureMap.getTextureCoords(Textures::GrassSide, TextureMap::RightBottom);
	_vertexBuffer[2].texCoord = _textureMap.getTextureCoords(Textures::GrassSide, TextureMap::RightTop);
	_vertexBuffer[3].texCoord = _textureMap.getTextureCoords(Textures::GrassSide, TextureMap::LeftTop);


	_vertexBuffer.update();
}
