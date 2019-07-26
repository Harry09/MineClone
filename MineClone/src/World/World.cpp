#include "World.hpp"

#include <FastNoise.h>

World::World()
	: _chunkManager(*this)
{
}

void World::init()
{
	_texture.loadFromFile("textures.jpg");

	_textureAtlas = std::make_unique<TextureAtlas>(_texture, 16);

	FastNoise noise;
	noise.SetNoiseType(FastNoise::NoiseType::Simplex);
	noise.SetFrequency(0.01f);
	
	std::vector<std::vector<int>> heightMap;

	const int ChunkCount = 10;

	const int Size = ChunkCount * 16;

	heightMap.resize(Size);
	
	printf("Generating height map...\n");

	for (int x = 0; x < Size; x++)
	{
		heightMap[x].resize(Size);

		for (int y = 0; y < Size; y++)
		{
			heightMap[x][y] = static_cast<int>(noise.GetNoise(static_cast<float>(x), static_cast<float>(y)) * 16);
		}
	}

	printf("Generating world...\n");

	for (int x = 0; x < ChunkCount; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int z = 0; z < ChunkCount; z++)
			{
				_chunks.push_back(std::make_unique<Chunk>(*this, glm::ivec3{ x, y - 1, z }, heightMap, *_textureAtlas));
				printf("%d %d\n", x, z);
			}
		}
	}

	printf("Generating mesh...\n");

	for (auto& chunk : _chunks)
	{
		chunk->generateMesh(*_textureAtlas);
	}
}

Chunk* World::getChunk(const glm::ivec3& pos) const
{
	auto it = std::find_if(_chunks.begin(), _chunks.end(), [&](auto& it) { return it->getPos() == pos; });

	if (it != _chunks.end())
	{
		return (*it).get();
	}

	return nullptr;
}

void World::draw(ShaderProgram& shaderProgram)
{
	_chunkManager.draw(shaderProgram);
}
