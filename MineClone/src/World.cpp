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
	noise.SetNoiseType(FastNoise::NoiseType::Simplex);
	noise.SetFrequency(0.01f);
	
	std::vector<std::vector<int>> heightMap;

	const int ChunkCount = 5;

	const int Size = ChunkCount * 16;

	heightMap.resize(Size);
	
	for (int x = 0; x < Size; x++)
	{
		heightMap[x].resize(Size);

		for (int y = 0; y < Size; y++)
		{
			heightMap[x][y] = static_cast<int>(noise.GetNoise(static_cast<float>(x), static_cast<float>(y)) * 16);
		}
	}

	for (int x = 0; x < ChunkCount; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int z = 0; z < ChunkCount; z++)
			{
				_chunks.push_back(std::make_unique<Chunk>(glm::ivec3{ x, y - 1, z }, heightMap, *_textureMap));
				printf("%d %d\n", x, z);
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
