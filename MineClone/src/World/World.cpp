#include "World.hpp"

#include <FastNoise.h>

World::World()
	: 
	_texture("textures.jpg"),
	_textureAtlas(_texture, 16),
	_chunkManager(*this)
{
}

void World::init()
{
	FastNoise noise;
	noise.SetNoiseType(FastNoise::NoiseType::Simplex);
	noise.SetFrequency(0.01f);

	std::vector<std::vector<int>> heightMap;

	const int ChunkCount = 3;

	const int Size = ChunkCount * 16;

	heightMap.resize(Size);

	printf("Generating height map...\n");

	for (int x = 0; x < Size; x++)
	{
		heightMap[x].resize(Size);

		for (int y = 0; y < Size; y++)
		{
			heightMap[x][y] = static_cast<int>(noise.GetNoise(static_cast<float>(x), static_cast<float>(y)) * 16 * 2);
		}
	}

	printf("Generating world...\n");

	for (int x = 0; x < ChunkCount; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			for (int z = 0; z < ChunkCount; z++)
			{
				_chunkManager.addChunk(glm::ivec3{ x, y, z }, heightMap, _textureAtlas);

				printf("%d %d\n", x, z);
			}
		}
	}

	printf("Generating mesh...\n");

	_chunkManager.updateMesh(_textureAtlas);
}

Chunk* World::getChunk(const glm::ivec3& pos) const
{
	return _chunkManager.getChunk(pos);
}

void World::removeBlock(const glm::ivec3& pos)
{
	auto chunk = getChunk(getChunkPos(pos));

	if (chunk == nullptr)
		return;
	
	chunk->removeBlock(getLocalPos(pos));
	chunk->generateMesh(_textureAtlas);
}

Block* World::getBlock(const glm::ivec3& pos) const
{
	auto chunk = getChunk(getChunkPos(pos));

	if (chunk != nullptr)
	{
		return chunk->getBlock(getLocalPos(pos));
	}

	return nullptr;
}

void World::drawChunks(ShaderProgram& shaderProgram)
{
	_chunkManager.drawChunks(shaderProgram);
}

void World::drawGrid(ShaderProgram& shaderProgram)
{
	_chunkManager.drawGrid(shaderProgram);
}

glm::ivec3 World::getChunkPos(const glm::ivec3& worldPos)
{
	auto chunkPos = worldPos / Chunk::Size;

	if (worldPos.x < 0)
		chunkPos.x--;

	if (worldPos.y < 0)
		chunkPos.y--;

	if (worldPos.z < 0)
		chunkPos.z--;

	return chunkPos;
}

glm::ivec3 World::getLocalPos(const glm::ivec3& worldPos)
{
	auto pos = glm::abs(worldPos % Chunk::Size);
	return pos;
}

glm::ivec3 World::getWorldPos(const glm::ivec3& localPos, const glm::ivec3& chunkPos)
{
	return chunkPos * Chunk::Size + localPos;
}
