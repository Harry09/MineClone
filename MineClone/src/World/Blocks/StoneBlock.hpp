#pragma once

#include "Block.hpp"

class StoneBlock : public Block
{
public:
	StoneBlock(ChunkSegment& chunk, const coords::LocalPos& localPos) noexcept
		: Block(chunk, localPos, Blocks::Stone)
	{
		setTexture<
			BlockFace::North,
			BlockFace::East,
			BlockFace::South,
			BlockFace::West,
			BlockFace::Top,
			BlockFace::Bottom>(TextureId::Stone);
	}
};