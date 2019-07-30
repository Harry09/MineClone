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

	const int ChunkCount = 2;

	const int Size = ChunkCount * 16;

	heightMap.resize(Size);

	printf("Generating world...\n");

	for (int x = -ChunkCount; x < ChunkCount; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			for (int z = -ChunkCount; z < ChunkCount; z++)
			{
				_chunkManager.addChunk(glm::ivec3{ x, y, z }, noise, _textureAtlas);

				printf("%d %d\n", x, z);
			}
		}
	}

	printf("Generating mesh...\n");

	_chunkManager.updateMesh(_textureAtlas);
}

Chunk* World::getChunk(const glm::ivec3& chunkPos) const
{
	return _chunkManager.getChunk(chunkPos);
}

void World::removeBlock(const glm::ivec3& worldPos)
{
	auto chunkPos = getChunkPos(worldPos);

	auto chunk = getChunk(chunkPos);

	if (chunk == nullptr)
		return;
	
	chunk->removeBlock(getLocalPos(worldPos));
	chunk->generateMesh(_textureAtlas);

	tryUpdateNearChunks(worldPos, chunkPos);
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
	glm::ivec3 chunkPos = worldPos;

	if (worldPos.x < 0)
		chunkPos.x = (chunkPos.x + 1) / (Chunk::Size) - 1;
	else
		chunkPos.x /= Chunk::Size;

	if (worldPos.y < 0)
		chunkPos.y = (chunkPos.y + 1) / (Chunk::Size) - 1;
	else
		chunkPos.y /= Chunk::Size;

	if (worldPos.z < 0)
		chunkPos.z = (chunkPos.z + 1) / (Chunk::Size) - 1;
	else
		chunkPos.z /= Chunk::Size;

	return chunkPos;
}

glm::ivec3 World::getLocalPos(const glm::ivec3& worldPos)
{
	auto localPos = glm::abs(worldPos);

	if (worldPos.x < 0)
		localPos.x = Chunk::Size - ((localPos.x - 1) % (Chunk::Size) + 1);
	else
		localPos.x %= Chunk::Size;

	if (worldPos.y < 0)
		localPos.y = Chunk::Size - ((localPos.y - 1) % (Chunk::Size) + 1);
	else
		localPos.y %= Chunk::Size;

	if (worldPos.z < 0)
		localPos.z = Chunk::Size - ((localPos.z - 1) % (Chunk::Size) + 1);
	else
		localPos.z %= Chunk::Size;

	return localPos;
}

glm::ivec3 World::getWorldPos(const glm::ivec3& localPos, const glm::ivec3& chunkPos)
{
	return chunkPos * Chunk::Size + localPos;
}

void World::tryUpdateNearChunks(const glm::ivec3& worldPos, const glm::ivec3& chunkPos)
{
	auto neighbors = getNeighborIfOnBound(worldPos);

	for (auto& neighbor : neighbors)
	{
		auto neighborChunk = getChunk(chunkPos + neighbor);

		if (neighborChunk == nullptr)
			continue;

		if (neighborChunk->getBlock(getLocalPos(worldPos + neighbor)) != nullptr)
		{
			neighborChunk->generateMesh(_textureAtlas);
		}
	}
}

std::vector<glm::ivec3> World::getNeighborIfOnBound(const glm::ivec3& worldPos)
{
	std::vector<glm::ivec3> result;

	auto localPos = getLocalPos(worldPos);

	if (localPos.x == 0)
		result.push_back(glm::ivec3{ -1, 0, 0 });
	else if (localPos.x == 15)
		result.push_back(glm::ivec3{ 1, 0, 0 });
	
	if (localPos.y == 0)
		result.push_back(glm::ivec3{ 0, -1, 0 });
	else if (localPos.y == 15)
		result.push_back(glm::ivec3{ 0, 1, 0 });

	if (localPos.z == 0)
		result.push_back(glm::ivec3{ 0, 0, -1 });
	else if (localPos.z == 15)
		result.push_back(glm::ivec3{ 0, 0, 1 });

	return result;
}
