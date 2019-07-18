#include "DirtBlock.hpp"

DirtBlock::DirtBlock() noexcept 
	: Block(Blocks::Dirt)
{
}

DirtBlock::DirtBlock(const glm::vec3& pos) noexcept
	: Block(pos, Blocks::Dirt)
{
}

const std::array<Vertex, 2 * 3 * 6> DirtBlock::getVertices(TextureMap& textureMap) const
{
	auto vertices = getMesh();

	texture<BlockSide::North>(vertices,  Textures::Dirt, textureMap);
	texture<BlockSide::East>(vertices,   Textures::Dirt, textureMap);
	texture<BlockSide::South>(vertices,  Textures::Dirt, textureMap);
	texture<BlockSide::West>(vertices,   Textures::Dirt, textureMap);
	texture<BlockSide::Top>(vertices,    Textures::Dirt, textureMap);
	texture<BlockSide::Bottom>(vertices, Textures::Dirt, textureMap);

	return vertices;
}
