#pragma once

#include "IWorldGenerator.hpp"

#include <array>

#include <FastNoise.h>

#include "Maths/Coords.hpp"
#include "World/Chunk/ChunkSegment.hpp"

class WorldGeneratorV1 : public IWorldGenerator
{
private:
	using HeightMapType = std::array<std::array<int, ChunkSegment::Size>, ChunkSegment::Size>;

private:
	FastNoise noise;

public:
	WorldGeneratorV1(World& world);

	Chunk* generateChunk(coords::ChunkPos&& chunkPos) override;

private:
	void generateChunkSegment(const coords::ChunkSegmentPos& segmentPos, ChunkSegment& segment);
};