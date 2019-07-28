#include "ChunkManager.hpp"

ChunkManager::ChunkManager(World& world)
	: _world(world)
{
}

ChunkManager::~ChunkManager()
{
}

Chunk* ChunkManager::getChunk(const glm::ivec3& pos) const
{
	auto it = std::find_if(_chunks.begin(), _chunks.end(), [&](auto& it) { return it->getPos() == pos; });

	if (it != _chunks.end())
	{
		return (*it).get();
	}

	return nullptr;
}

void ChunkManager::addChunk(const glm::ivec3& pos, const std::vector<std::vector<int>>& heightMap, TextureAtlas& textureAtlas)
{
	_chunks.push_back(std::make_unique<Chunk>(_world, pos, heightMap, textureAtlas));
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
	for (auto& chunk : _chunks)
	{
		chunk->drawChunks(shaderProgram);
	}
}

void ChunkManager::drawGrid(ShaderProgram& shaderProgram)
{
	for (auto& chunk : _chunks)
	{
		chunk->drawGrid(shaderProgram);
	}
}
