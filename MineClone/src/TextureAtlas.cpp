#include "TextureAtlas.hpp"

TextureAtlas::TextureAtlas(Texture& texture, unsigned singleTextureSize)
	: _texture(texture), _singleTextureSize(singleTextureSize)
{
}

glm::vec2 TextureAtlas::getTextureCoords(unsigned row, unsigned column, Corner corner) const
{
	glm::vec2 coords;

	int offsetX = 0, offsetY = 0;

	switch (corner)
	{
		case RightTop:
			offsetX = 1;
			break;
		case LeftBottom:
			offsetY = 1;
			break;
		case RightBottom:
			offsetX = 1;
			offsetY = 1;
			break;
	}

	coords.x = static_cast<float>(_singleTextureSize * (row + offsetX)) / _texture.getSize().x;
	coords.y = static_cast<float>(_singleTextureSize * (column + offsetY)) / _texture.getSize().y;

	return coords;
}

glm::vec2 TextureAtlas::getTextureCoords(TextureId textureId, Corner corner) const
{
	switch (textureId)
	{
		case TextureId::Dirt:
			return getTextureCoords(0, 0, corner);
		case TextureId::GrassSide:
			return getTextureCoords(1, 0, corner);
		case TextureId::GrassTop:
			return getTextureCoords(2, 0, corner);
		case TextureId::Stone:
			return getTextureCoords(3, 0, corner);

		case TextureId::None:
		default:
			return getTextureCoords(15, 15, corner);
	}
}
