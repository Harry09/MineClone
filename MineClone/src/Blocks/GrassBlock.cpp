#include "GrassBlock.hpp"

GrassBlock::GrassBlock() noexcept
	: Block(Blocks::Grass)
{
}

GrassBlock::GrassBlock(const glm::vec3& pos) noexcept
	: Block(pos, Blocks::Grass)
{
}

std::array<Vertex, 4 * 6> GrassBlock::getVertices(TextureMap& textureMap)
{
	auto vertices = getMesh();

	texture<TexturingSide::North>(vertices,  Textures::GrassSide, textureMap);
	texture<TexturingSide::East>(vertices,   Textures::GrassSide, textureMap);
	texture<TexturingSide::South>(vertices,  Textures::GrassSide, textureMap);
	texture<TexturingSide::West>(vertices,   Textures::GrassSide, textureMap);
	texture<TexturingSide::Top>(vertices,    Textures::GrassTop, textureMap);
	texture<TexturingSide::Bottom>(vertices, Textures::Dirt, textureMap);

	for (int i = 0; i < 4 * 6; i++)
	{
		vertices[i].position += _pos;
	}

	return vertices;

}
