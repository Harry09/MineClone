#pragma once

#include "Block.hpp"

class GrassBlock : public Block
{
public:
	GrassBlock(Chunk& chunk, const glm::ivec3& pos) noexcept
		: Block(chunk, pos, Blocks::Grass)
	{
		setTexture<
			BlockSide::North,
			BlockSide::East,
			BlockSide::South,
			BlockSide::West>(Textures::GrassSide);

		setTexture<BlockSide::Top>(Textures::GrassTop);
		setTexture<BlockSide::Bottom>(Textures::Dirt);
	}
};