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
	_chunkManager(*this),
	_worldGenerator(std::make_unique<WorldGeneratorV1>(*this))
{

}

void World::init()
{
	// generate spawn
	_chunkManager.addChunk(_worldGenerator->generateChunk({ 0, 0 }));

	_chunkManager.addChunk(_worldGenerator->generateChunk({ 1, 0 }));
	_chunkManager.addChunk(_worldGenerator->generateChunk({ 0, 1 }));
	_chunkManager.addChunk(_worldGenerator->generateChunk({ 1, 1 }));

	_chunkManager.addChunk(_worldGenerator->generateChunk({ -1, 0 }));
	_chunkManager.addChunk(_worldGenerator->generateChunk({ 0, -1 }));
	_chunkManager.addChunk(_worldGenerator->generateChunk({ -1, -1 }));

	_chunkManager.addChunk(_worldGenerator->generateChunk({ 1, -1 }));
	_chunkManager.addChunk(_worldGenerator->generateChunk({ -1, 1 }));

	_chunkManager.updateMeshes();
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
	chunk->generateMesh();

	tryUpdateNearbyChunks(worldPos, chunkPos);
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

void World::tryUpdateNearbyChunks(const coords::WorldPos& worldPos, const coords::ChunkSegmentPos& chunkSegmentPos)
{
	auto neighbors = getNeighborIfOnBound(worldPos);

	for (auto& neighbor : neighbors)
	{
		auto neighborChunk = getChunkSegment(chunkSegmentPos + neighbor);

		if (neighborChunk == nullptr)
			continue;

		if (neighborChunk->getBlock(coords::getLocalPos(worldPos + neighbor)) != nullptr)
		{
			neighborChunk->generateMesh(true);
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
