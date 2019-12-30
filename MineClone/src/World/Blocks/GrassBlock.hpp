#pragma once

#include "Block.hpp"

class GrassBlock : public Block
{
public:
	GrassBlock(ChunkSegment& chunk, const coords::LocalPos& localPos) noexcept
		: Block(chunk, localPos, Blocks::Grass)
	{
		setTexture<
			BlockFace::North,
			BlockFace::East,
			BlockFace::South,
			BlockFace::West>(TextureId::GrassSide);

		setTexture<BlockFace::Top>(TextureId::GrassTop);
		setTexture<BlockFace::Bottom>(TextureId::Dirt);
	}
};