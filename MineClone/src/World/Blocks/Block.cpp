#include "Block.hpp"

#include "World/World.hpp"

Block::Block(ChunkSegment& chunk, const coords::LocalPos& localPos, Blocks blockType) noexcept
	: 
	_chunk(chunk),
	_localPos(localPos),
	_blockType(blockType)
{
}

Block::Block(const Block& other) noexcept
	:
	_chunk(other._chunk),
	_localPos(other._localPos),
	_blockType(other._blockType)
{

}

Block& Block::operator=(const Block& other) noexcept
{
	_localPos = other._localPos;
	_blockType = other._blockType;

	return *this;
}

Block::Block(Block&& other) noexcept
	:
	_chunk(other._chunk),
	_localPos(std::move(other._localPos)),
	_blockType(std::move(other._blockType))
{

}

Block& Block::operator=(Block&& other) noexcept
{
	_localPos = std::move(other._localPos);
	_blockType = std::move(other._blockType);

	return *this;
}

coords::WorldPos Block::getWorldPos() const
{
	return World::getWorldPos(_localPos, _chunk.getPos());
}

Block* Block::getNeighbor(BlockSide side) const
{
	return _chunk.getNeighborOfBlock(this, side);
}
