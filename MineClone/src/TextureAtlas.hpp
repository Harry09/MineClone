#pragma once

#include <array>

#include "Graphics/Texture.hpp"

#include "World/Blocks/Blocks.hpp"

enum TextureId
{
	Dirt,
	GrassSide,
	GrassTop,
	Stone,

	None 
};

class TextureAtlas
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
	TextureAtlas(Texture& texture, unsigned singleTextureSize);

	glm::vec2 getTextureCoords(unsigned row, unsigned column, Corner corner) const;
	glm::vec2 getTextureCoords(TextureId textureId, Corner corner) const;

	auto& getTexture() { return _texture; }
};
