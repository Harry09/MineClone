#include "Block.hpp"

#include "World/Chunk.hpp"

glm::ivec3 getBlockSideDirection(BlockSide side)
{
	switch (side)
	{
	case BlockSide::North:
		return { 0, 0, -1 };
	case BlockSide::East:
		return { 1, 0, 0 };
	case BlockSide::South:
		return { 0, 0, 1 };
	case BlockSide::West:
		return { -1, 0, 0 };
	case BlockSide::Top:
		return { 0, 1, 0 };
	case BlockSide::Bottom:
		return { 0, -1, 0 };
	}

	return { 0, 0, 0 };
}

Block::Block(Chunk& chunk, const glm::ivec3& pos, Blocks blockType) noexcept
	: 
	_chunk(chunk),
	_pos(pos),
	_blockType(blockType)
{
}

Block::Block(const Block& other) noexcept
	:
	_chunk(other._chunk),
	_pos(other._pos),
	_blockType(other._blockType)
{

}

Block& Block::operator=(const Block& other) noexcept
{
	_pos = other._pos;
	_blockType = other._blockType;

	return *this;
}

Block::Block(Block&& other) noexcept
	:
	_chunk(other._chunk),
	_pos(std::move(other._pos)),
	_blockType(std::move(other._blockType))
{

}

Block& Block::operator=(Block&& other) noexcept
{
	_pos = std::move(other._pos);
	_blockType = std::move(other._blockType);

	return *this;
}

glm::ivec3 Block::getWorldPosition() const
{
	return _chunk.getPos() * (Chunk::Size - 1) + _pos;
}

Block* Block::getNeighbor(BlockSide side) const
{
	return _chunk.getNeighborOfBlock(this, side);
}
