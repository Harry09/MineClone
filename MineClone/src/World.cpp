#include "World.hpp"

World::World()
{
}

void World::init()
{
	_texture.loadFromFile("textures.jpg");

	_textureMap = std::make_unique<TextureMap>(_texture, 16);
	

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int z = 0; z < 3; z++)
			{
				_chunks.push_back(std::make_unique<Chunk>(glm::ivec3{ x, y, z }, *_textureMap));
				printf("%d %d %d done\n", x, y, z);
			}
		}
	}
}

void World::draw(ShaderProgram& shaderProgram)
{
	for (auto& chunk : _chunks)
	{
		chunk->draw(shaderProgram);
	}
}
