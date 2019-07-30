#include "World.hpp"

#include <FastNoise.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Graphics/Camera.hpp"
#include "Game.hpp"


World::World(Camera& camera)
	: 
	_camera(camera),
	_frustumView(camera),
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

	const int ChunkCount = 4;

	const int Size = ChunkCount * 16;

	printf("Generating world...\n");

	for (int x = -ChunkCount; x < ChunkCount; x++)
	{
		for (int z = -ChunkCount; z < ChunkCount; z++)
		{
			_chunkManager.addChunk(coords::ChunkPos{ x, z }, noise, _textureAtlas);

			printf("%d %d\n", x, z);
		}
	}

	printf("Generating mesh...\n");

	_chunkManager.updateMesh(_textureAtlas);
}

Chunk* World::getChunk(const coords::ChunkPos& chunkPos) const
{
	return _chunkManager.getChunk(chunkPos);
}

ChunkSegment* World::getChunkSegment(const coords::ChunkSegmentPos& chunkSegmentPos) const
{
	return _chunkManager.getChunkSegment(chunkSegmentPos);
}

void World::removeBlock(const coords::WorldPos& worldPos)
{
	auto chunkPos = getChunkSegmentPos(worldPos);

	auto chunk = getChunkSegment(chunkPos);

	if (chunk == nullptr)
		return;
	
	chunk->removeBlock(getLocalPos(worldPos));
	chunk->generateMesh(_textureAtlas);

	tryUpdateNearChunks(worldPos, chunkPos);
}

Block* World::getBlock(const coords::WorldPos& worldPos) const
{
	auto chunk = getChunkSegment(getChunkSegmentPos(worldPos));

	if (chunk != nullptr)
	{
		return chunk->getBlock(getLocalPos(worldPos));
	}

	return nullptr;
}

void World::update()
{
	_frustumView.update();
}

void World::drawChunks(ShaderProgram& shaderProgram)
{
	_chunkManager.drawChunks(shaderProgram);
}

void World::drawGrid(ShaderProgram& shaderProgram)
{
	_chunkManager.drawGrid(shaderProgram);
}

coords::ChunkPos World::getChunkPos(const coords::WorldPos& worldPos)
{
	coords::ChunkPos chunkPos = { worldPos.x, worldPos.z };

	// x
	if (worldPos.x < 0)
		chunkPos.x = (chunkPos.x + 1) / (ChunkSegment::Size) - 1;
	else
		chunkPos.x /= ChunkSegment::Size;

	// z
	if (worldPos.z < 0)
		chunkPos.y = (chunkPos.y + 1) / (ChunkSegment::Size) - 1;
	else
		chunkPos.y /= ChunkSegment::Size;

	return chunkPos;
}

coords::ChunkSegmentPos World::getChunkSegmentPos(const coords::WorldPos& worldPos)
{
	coords::ChunkSegmentPos chunkSegmentPos = worldPos;

	if (worldPos.x < 0)
		chunkSegmentPos.x = (chunkSegmentPos.x + 1) / (ChunkSegment::Size) - 1;
	else
		chunkSegmentPos.x /= ChunkSegment::Size;

	if (worldPos.y < 0)
		chunkSegmentPos.y = (chunkSegmentPos.y + 1) / (ChunkSegment::Size) - 1;
	else
		chunkSegmentPos.y /= ChunkSegment::Size;

	if (worldPos.z < 0)
		chunkSegmentPos.z = (chunkSegmentPos.z + 1) / (ChunkSegment::Size) - 1;
	else
		chunkSegmentPos.z /= ChunkSegment::Size;

	return chunkSegmentPos;
}

coords::LocalPos World::getLocalPos(const coords::WorldPos& worldPos)
{
	auto localPos = glm::abs(worldPos);

	if (worldPos.x < 0)
		localPos.x = ChunkSegment::Size - ((localPos.x - 1) % (ChunkSegment::Size) + 1);
	else
		localPos.x %= ChunkSegment::Size;

	if (worldPos.y < 0)
		localPos.y = ChunkSegment::Size - ((localPos.y - 1) % (ChunkSegment::Size) + 1);
	else
		localPos.y %= ChunkSegment::Size;

	if (worldPos.z < 0)
		localPos.z = ChunkSegment::Size - ((localPos.z - 1) % (ChunkSegment::Size) + 1);
	else
		localPos.z %= ChunkSegment::Size;

	return localPos;
}

coords::WorldPos World::getWorldPos(const coords::LocalPos& localPos, const coords::ChunkSegmentPos& chunkSegmentPos)
{
	return chunkSegmentPos * ChunkSegment::Size + localPos;
}

void World::tryUpdateNearChunks(const coords::WorldPos& worldPos, const coords::ChunkSegmentPos& chunkSegmentPos)
{
	auto neighbors = getNeighborIfOnBound(worldPos);

	for (auto& neighbor : neighbors)
	{
		auto neighborChunk = getChunkSegment(chunkSegmentPos + neighbor);

		if (neighborChunk == nullptr)
			continue;

		if (neighborChunk->getBlock(getLocalPos(worldPos + neighbor)) != nullptr)
		{
			neighborChunk->generateMesh(_textureAtlas);
		}
	}
}

std::vector<glm::ivec3> World::getNeighborIfOnBound(const coords::WorldPos& worldPos)
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
