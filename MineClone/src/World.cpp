#include "World.hpp"

#include <FastNoise.h>

World::World()
{
}

void World::init()
{
	_texture.loadFromFile("textures.jpg");

	_textureMap = std::make_unique<TextureMap>(_texture, 16);

	FastNoise noise;
	noise.SetNoiseType(FastNoise::NoiseType::Perlin);
	noise.SetFrequency(0.05f);
	
	for (int x = 0; x < 10; x++)
	{
		for (int z = 0; z < 10; z++)
		{
			_chunks.push_back(std::make_unique<Chunk>(glm::ivec3{ x, 0, z }, noise, *_textureMap));
			printf("%d %d\n", x, z);
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
