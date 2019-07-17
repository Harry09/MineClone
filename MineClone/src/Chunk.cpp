#include "Chunk.hpp"

#include "Blocks/DirtBlock.hpp"
#include "Blocks/GrassBlock.hpp"
#include "Blocks/StoneBlock.hpp"

Chunk::Chunk()
{
}

Chunk::~Chunk()
{
}

void Chunk::init()
{
	_texture.loadFromFile("textures.jpg");

	TextureMap textureMap(_texture, 16);

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			GrassBlock grass(glm::vec3{ i, 0.f, j });
			grass.create(textureMap);
			_blocks.push_back(std::move(grass));

			StoneBlock stone(glm::vec3{ i, -1.f, j });
			stone.create(textureMap);
			_blocks.push_back(std::move(stone));
		}
	}
}

void Chunk::draw(ShaderProgram& shaderProgram)
{
	for (auto& block : _blocks)
	{
		block.draw(shaderProgram);
	}
}
