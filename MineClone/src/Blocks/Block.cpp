#include "Block.hpp"

#include "Chunk.hpp"

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

const std::array<Vertex, 2 * 3 * 6> Block::getVertices(TextureMap& textureMap) const
{
	auto vertices = getMesh();

	texture<BlockSide::North>(vertices, textureMap);
	texture<BlockSide::East>(vertices,  textureMap);
	texture<BlockSide::South>(vertices, textureMap);
	texture<BlockSide::West>(vertices,  textureMap);
	texture<BlockSide::Top>(vertices,   textureMap);
	texture<BlockSide::Bottom>(vertices,textureMap);

	return vertices;
}
