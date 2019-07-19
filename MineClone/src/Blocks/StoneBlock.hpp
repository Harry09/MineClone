#pragma once

#include "Block.hpp"

class StoneBlock : public Block
{
public:
	StoneBlock(const glm::ivec3& pos) noexcept
		: Block(pos, Blocks::Stone)
	{
		setTexture<
			BlockSide::North,
			BlockSide::East,
			BlockSide::South,
			BlockSide::West,
			BlockSide::Top,
			BlockSide::Bottom>(Textures::Stone);
	}
};