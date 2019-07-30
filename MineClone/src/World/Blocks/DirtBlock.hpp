#pragma once

#include "Block.hpp"

class DirtBlock : public Block
{
public:
	DirtBlock(ChunkSegment& chunk, const coords::LocalPos& localPos) noexcept
		: Block(chunk, localPos, Blocks::Dirt)
	{
		setTexture<
			BlockSide::North,
			BlockSide::East,
			BlockSide::South,
			BlockSide::West,
			BlockSide::Top,
			BlockSide::Bottom>(TextureId::Dirt);
	}
};
