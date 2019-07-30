﻿#pragma once

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

	Chunk* getChunk(const glm::ivec3& chunkPos) const;
	ChunkSegment* getChunkSegment(const glm::ivec3& chunkPos) const;
	void addChunk(const glm::ivec2& posXZ, FastNoise& noise, TextureAtlas& textureAtlas);

	void updateMesh(TextureAtlas& textureAtlas);

	void drawChunks(ShaderProgram& shaderProgram);
	void drawGrid(ShaderProgram& shaderProgram);
};
