#include "Block.hpp"

#include "Chunk.hpp"

Block::Block(const glm::ivec3& pos, Blocks blockType) noexcept
	: 
	_pos(pos),
	_blockType(blockType)
{
	_flatPos = (pos.x + Chunk::Size.x * (pos.y + Chunk::Size.y * pos.z)) * 36;
}

Block::Block(const Block& other) noexcept
	:
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
