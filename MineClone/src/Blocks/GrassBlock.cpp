#include "GrassBlock.hpp"

GrassBlock::GrassBlock() noexcept
	: Block(Blocks::Grass)
{
}

GrassBlock::GrassBlock(const glm::vec3& pos) noexcept
	: Block(pos, Blocks::Grass)
{
}

const std::array<Vertex, 2 * 3 * 6> GrassBlock::getVertices(TextureMap& textureMap) const
{
	auto vertices = getMesh();

	texture<BlockSide::North>(vertices,  Textures::GrassSide, textureMap);
	texture<BlockSide::East>(vertices,   Textures::GrassSide, textureMap);
	texture<BlockSide::South>(vertices,  Textures::GrassSide, textureMap);
	texture<BlockSide::West>(vertices,   Textures::GrassSide, textureMap);
	texture<BlockSide::Top>(vertices,    Textures::GrassTop, textureMap);
	texture<BlockSide::Bottom>(vertices, Textures::Dirt, textureMap);

	return vertices;
}
