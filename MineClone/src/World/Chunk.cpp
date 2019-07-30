#include "Chunk.hpp"

#include <FastNoise.h>

Chunk::Chunk(World& world, const glm::ivec2& posXZ, FastNoise& noise, TextureAtlas& textureAtlas)
	: _posXZ(posXZ)
{
	std::array<std::array<int, ChunkSegment::Size>, ChunkSegment::Size> heightMap;

	for (int x = 0; x < ChunkSegment::Size; x++)
	{
		for (int z = 0; z < ChunkSegment::Size; z++)
		{
			float xx = static_cast<float>(x + posXZ.x * ChunkSegment::Size);
			float zz = static_cast<float>(z + posXZ.y * ChunkSegment::Size);

			heightMap[x][z] = static_cast<int>((noise.GetNoise(xx, zz) + 0.8f) * 16);
		}
	}

	_segments.reserve(Chunk::Height);

	for (int i = 0; i < Chunk::Height; i++)
	{
		_segments.push_back(std::make_unique<ChunkSegment>(world, glm::ivec3 {posXZ.x, i, posXZ.y}, heightMap, textureAtlas));
	}
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
