#pragma once

#include "Block.hpp"

class GrassBlock : public Block
{
public:
	GrassBlock(ChunkSegment& chunk, const glm::ivec3& pos) noexcept
		: Block(chunk, pos, Blocks::Grass)
	{
		setTexture<
			BlockSide::North,
			BlockSide::East,
			BlockSide::South,
			BlockSide::West>(TextureId::GrassSide);

		setTexture<BlockSide::Top>(TextureId::GrassTop);
		setTexture<BlockSide::Bottom>(TextureId::Dirt);
	}
};