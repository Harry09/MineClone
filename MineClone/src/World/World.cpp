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
	auto chunkPos = coords::getChunkSegmentPos(worldPos);

	auto chunk = getChunkSegment(chunkPos);

	if (chunk == nullptr)
		return;
	
	chunk->removeBlock(coords::getLocalPos(worldPos));
	chunk->generateMesh(_textureAtlas);

	tryUpdateNearChunks(worldPos, chunkPos);
}

Block* World::getBlock(const coords::WorldPos& worldPos) const
{
	auto chunk = getChunkSegment(coords::getChunkSegmentPos(worldPos));

	if (chunk != nullptr)
	{
		return chunk->getBlock(coords::getLocalPos(worldPos));
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

void World::tryUpdateNearChunks(const coords::WorldPos& worldPos, const coords::ChunkSegmentPos& chunkSegmentPos)
{
	auto neighbors = getNeighborIfOnBound(worldPos);

	for (auto& neighbor : neighbors)
	{
		auto neighborChunk = getChunkSegment(chunkSegmentPos + neighbor);

		if (neighborChunk == nullptr)
			continue;

		if (neighborChunk->getBlock(coords::getLocalPos(worldPos + neighbor)) != nullptr)
		{
			neighborChunk->generateMesh(_textureAtlas);
		}
	}
}

std::vector<glm::ivec3> World::getNeighborIfOnBound(const coords::WorldPos& worldPos)
{
	std::vector<glm::ivec3> result;

	auto localPos = coords::getLocalPos(worldPos);

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
