#pragma once

#include "Block.hpp"

class GrassBlock : public Block
{
public:
	GrassBlock(const glm::vec3& pos) noexcept
		: Block(pos, Blocks::Grass)
	{
		setTexture(BlockSide::North,  Textures::GrassSide);
		setTexture(BlockSide::East,   Textures::GrassSide);
		setTexture(BlockSide::South,  Textures::GrassSide);
		setTexture(BlockSide::West,   Textures::GrassSide);
		setTexture(BlockSide::Top,    Textures::GrassTop);
		setTexture(BlockSide::Bottom, Textures::Dirt);
	}
};