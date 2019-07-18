#include "Block.hpp"

Block::Block(Blocks blockType) noexcept
	: _blockType(blockType)
{
}

Block::Block(const glm::vec3& pos, Blocks blockType) noexcept
	: 
	_pos(pos),
	_blockType(blockType)
{
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
	_blockType(std::move(other._blockType)),
	_mesh(std::move(other._mesh))
{

}

Block& Block::operator=(Block&& other) noexcept
{
	_pos = std::move(other._pos);
	_blockType = std::move(other._blockType);
	_mesh = std::move(other._mesh);

	return *this;
}

void Block::create(TextureMap& map)
{
	auto vertices = getVertices(map);

	_mesh = std::make_unique<VertexBuffer>(vertices.data(), vertices.size(), PrimitiveType::Triangles);
	_mesh->setTexture(map.getTexture());
}

void Block::draw(ShaderProgram& shaderProgram)
{
	_mesh->draw(shaderProgram);
}
