#pragma once

#include "Block.hpp"

class StoneBlock : public Block
{
public:
	StoneBlock(ChunkSegment& chunk, const coords::LocalPos& localPos) noexcept
		: Block(chunk, localPos, Blocks::Stone)
	{
		setTexture<
			BlockSide::North,
			BlockSide::East,
			BlockSide::South,
			BlockSide::West,
			BlockSide::Top,
			BlockSide::Bottom>(TextureId::Stone);
	}
};