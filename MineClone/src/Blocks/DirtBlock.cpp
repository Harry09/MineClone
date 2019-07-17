#include "DirtBlock.hpp"

DirtBlock::DirtBlock() noexcept 
	: Block(Blocks::Dirt)
{
}

DirtBlock::DirtBlock(const glm::vec3& pos) noexcept
	: Block(pos, Blocks::Dirt)
{
}

std::array<Vertex, 4 * 6> DirtBlock::getVertices(TextureMap& textureMap)
{
	auto vertices = getMesh();

	texture<TexturingSide::North>(vertices,  Textures::Dirt, textureMap);
	texture<TexturingSide::East>(vertices,   Textures::Dirt, textureMap);
	texture<TexturingSide::South>(vertices,  Textures::Dirt, textureMap);
	texture<TexturingSide::West>(vertices,   Textures::Dirt, textureMap);
	texture<TexturingSide::Top>(vertices,    Textures::Dirt, textureMap);
	texture<TexturingSide::Bottom>(vertices, Textures::Dirt, textureMap);

	for (int i = 0; i < 4 * 6; i++)
	{
		vertices[i].position += _pos;
	}

	return vertices;
}
