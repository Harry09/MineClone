#include "Chunk.hpp"

#include <FastNoise.h>

Chunk::Chunk(World& world, const coords::ChunkPos& chunkPos, FastNoise& noise, TextureAtlas& textureAtlas)
	: _chunkPos(chunkPos)
{
	_segments.resize(Chunk::Height);
}

void Chunk::addChunkSegment(std::unique_ptr<ChunkSegment>& segment)
{
	auto y = segment->getChunkSegmentPos().y;

	_segments[y] = std::move(segment);
}

ChunkSegment* Chunk::getChunkSegment(int posZ)
{
	if (posZ < 0 || posZ > _segments.size() - 1)
		return nullptr;

	return _segments[posZ].get();
}

void Chunk::generateMesh(TextureAtlas& textureAtlas)
{
	for (auto& segment : _segments)
	{
		segment->generateMesh(textureAtlas);
	}
}

void Chunk::drawChunks(ShaderProgram& shaderProgram)
{
	for (auto& segment : _segments)
	{
		segment->drawChunks(shaderProgram);
	}
}

void Chunk::drawGrid(ShaderProgram& shaderProgram)
{
	for (auto& segment : _segments)
	{
		segment->drawGrid(shaderProgram);
	}
}
