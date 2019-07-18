#pragma once

#include "Block.hpp"

class DirtBlock : public Block
{
public:
	DirtBlock(const glm::vec3& pos) noexcept
		: Block(pos, Blocks::Dirt)
	{
		setTexture(BlockSide::North,  Textures::Dirt);
		setTexture(BlockSide::East,   Textures::Dirt);
		setTexture(BlockSide::South,  Textures::Dirt);
		setTexture(BlockSide::West,   Textures::Dirt);
		setTexture(BlockSide::Top,    Textures::Dirt);
		setTexture(BlockSide::Bottom, Textures::Dirt);
	}
};
