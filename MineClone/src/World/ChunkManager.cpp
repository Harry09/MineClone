#include "ChunkManager.hpp"

#include "World.hpp"

ChunkManager::ChunkManager(World& world)
	: _world(world)
{
}

ChunkManager::~ChunkManager()
{
}

Chunk* ChunkManager::getChunk(const glm::ivec3& chunkPos) const
{
	auto posXZ = glm::ivec2{ chunkPos.x, chunkPos.z };

	auto it = std::find_if(_chunks.begin(), _chunks.end(), [&](auto& it) { return it->getPosXZ() == posXZ; });

	if (it != _chunks.end())
	{
		return (*it).get();
	}

	return nullptr;
}

ChunkSegment* ChunkManager::getChunkSegment(const glm::ivec3& chunkPos) const
{
	auto chunk = getChunk(chunkPos);

	if (chunk == nullptr)
		return nullptr;

	return chunk->getChunkSegment(chunkPos.y);
}

void ChunkManager::addChunk(const glm::ivec2& posXZ, FastNoise& noise, TextureAtlas& textureAtlas)
{
	_chunks.push_back(std::make_unique<Chunk>(_world, posXZ, noise, textureAtlas));
}

void ChunkManager::updateMesh(TextureAtlas& textureAtlas)
{
	for (auto& chunk : _chunks)
	{
		chunk->generateMesh(textureAtlas);
	}
}

void ChunkManager::drawChunks(ShaderProgram& shaderProgram)
{
	auto& frustumView = _world.getFrustumView();

	for (auto& chunk : _chunks)
	{
		auto posXYZ = glm::ivec3 { chunk->getPosXZ().x * ChunkSegment::Size, 0, chunk->getPosXZ().y * ChunkSegment::Size };

		if (frustumView.isBoxInFOV(posXYZ, glm::ivec3 { ChunkSegment::Size, 0, ChunkSegment::Size }))
		{
			chunk->drawChunks(shaderProgram);
		}
	}
}

void ChunkManager::drawGrid(ShaderProgram& shaderProgram)
{
	for (auto& chunk : _chunks)
	{
		chunk->drawGrid(shaderProgram);
	}
}
