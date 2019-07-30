#pragma once

#include "Block.hpp"

class GrassBlock : public Block
{
public:
	GrassBlock(ChunkSegment& chunk, const coords::LocalPos& localPos) noexcept
		: Block(chunk, localPos, Blocks::Grass)
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