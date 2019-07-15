#pragma once

#include <array>

#include "Graphics/Texture.hpp"

#include "Textures.hpp"

class TextureMap
{
public:
	enum Corner
	{
		LeftTop,
		RightTop,
		LeftBottom,
		RightBottom
	};

private:
	Texture& _texture;

	unsigned _singleTextureSize;

public:
	TextureMap(Texture& texture, unsigned singleTextureSize);

	glm::vec2 getTextureCoords(unsigned row, unsigned column, Corner corner);
	glm::vec2 getTextureCoords(Textures textureId, Corner corner);
};
