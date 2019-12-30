#pragma once

#include "Block.hpp"

class DirtBlock : public Block
{
public:
	DirtBlock(ChunkSegment& chunk, const coords::LocalPos& localPos) noexcept
		: Block(chunk, localPos, Blocks::Dirt)
	{
		setTexture<
			BlockFace::North,
			BlockFace::East,
			BlockFace::South,
			BlockFace::West,
			BlockFace::Top,
			BlockFace::Bottom>(TextureId::Dirt);
	}
};
