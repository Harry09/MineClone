#include "StoneBlock.hpp"

StoneBlock::StoneBlock() noexcept
	: Block(Blocks::Stone)
{
}

StoneBlock::StoneBlock(const glm::vec3& pos) noexcept
	: Block(pos, Blocks::Stone)
{
}

const std::array<Vertex, 2 * 3 * 6> StoneBlock::getVertices(TextureMap& textureMap) const
{
	auto vertices = getMesh();

	texture<BlockSide::North>(vertices,  Textures::Stone, textureMap);
	texture<BlockSide::East>(vertices,   Textures::Stone, textureMap);
	texture<BlockSide::South>(vertices,  Textures::Stone, textureMap);
	texture<BlockSide::West>(vertices,   Textures::Stone, textureMap);
	texture<BlockSide::Top>(vertices,    Textures::Stone, textureMap);
	texture<BlockSide::Bottom>(vertices, Textures::Stone, textureMap);

	return vertices;
}
