#pragma once

#include "Block.hpp"

class StoneBlock : public Block
{
public:
	StoneBlock(const glm::vec3& pos) noexcept
		: Block(pos, Blocks::Stone)
	{
		setTexture(BlockSide::North,  Textures::Stone);
		setTexture(BlockSide::East,   Textures::Stone);
		setTexture(BlockSide::South,  Textures::Stone);
		setTexture(BlockSide::West,   Textures::Stone);
		setTexture(BlockSide::Top,    Textures::Stone);
		setTexture(BlockSide::Bottom, Textures::Stone);
	}
};