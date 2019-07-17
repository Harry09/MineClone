#include "StoneBlock.hpp"

StoneBlock::StoneBlock() noexcept
	: Block(Blocks::Stone)
{
}

StoneBlock::StoneBlock(const glm::vec3& pos) noexcept
	: Block(pos, Blocks::Stone)
{
}

std::array<Vertex, 4 * 6> StoneBlock::getVertices(TextureMap& textureMap)
{
	auto vertices = getMesh();

	texture<TexturingSide::North>(vertices,  Textures::Stone, textureMap);
	texture<TexturingSide::East>(vertices,   Textures::Stone, textureMap);
	texture<TexturingSide::South>(vertices,  Textures::Stone, textureMap);
	texture<TexturingSide::West>(vertices,   Textures::Stone, textureMap);
	texture<TexturingSide::Top>(vertices,    Textures::Stone, textureMap);
	texture<TexturingSide::Bottom>(vertices, Textures::Stone, textureMap);

	return vertices;
}
