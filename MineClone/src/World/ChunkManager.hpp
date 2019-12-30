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
	void addChunk(const coords::ChunkPos& chunkPos, FastNoise& noise, TextureAtlas& textureAtlas);

	void updateMeshes(TextureAtlas& textureAtlas);

	void drawChunks(ShaderProgram& shaderProgram);
	void drawGrid(ShaderProgram& shaderProgram);
};
