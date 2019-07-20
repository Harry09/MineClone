﻿#pragma once

#include "Block.hpp"

class DirtBlock : public Block
{
public:
	DirtBlock(Chunk& chunk, const glm::ivec3& pos) noexcept
		: Block(chunk, pos, Blocks::Dirt)
	{
		setTexture<
			BlockSide::North,
			BlockSide::East,
			BlockSide::South,
			BlockSide::West,
			BlockSide::Top,
			BlockSide::Bottom>(Textures::Dirt);
	}
};