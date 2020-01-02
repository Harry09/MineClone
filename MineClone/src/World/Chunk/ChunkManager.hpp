#pragma once

#include <vector>
#include <memory>

#include "Chunk.hpp"
#include "ChunkSegment.hpp"

class FastNoise;

class ChunkManager
{
private:
	std::vector<std::unique_ptr<Chunk>> _chunks;

	World& _world;

public:
	ChunkManager(World& world);
	~ChunkManager();

	Chunk* getChunk(const coords::ChunkPos& chunkPos) const;
	ChunkSegment* getChunkSegment(const coords::ChunkSegmentPos& chunkSegmentPos) const;

	void addChunk(Chunk* chunk);

	void updateMeshes();

	void drawChunks(ShaderProgram& shaderProgram);
	void drawGrid(ShaderProgram& shaderProgram);
};
