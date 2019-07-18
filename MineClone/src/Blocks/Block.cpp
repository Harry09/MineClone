#include "Block.hpp"

#include "Chunk.hpp"

Block::Block(Blocks blockType) noexcept
	: _blockType(blockType)
{
}

Block::Block(const glm::vec3& pos, Blocks blockType) noexcept
	: 
	_pos(pos),
	_blockType(blockType)
{
	auto ipos = glm::ivec3(pos);

	_flatPos = (ipos.x + Chunk::Size.x * (ipos.y + Chunk::Size.y * ipos.z)) * 36;
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

Block::~Block()
{
}
