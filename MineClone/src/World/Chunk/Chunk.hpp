#pragma once

#include "ChunkSegment.hpp"

class FastNoise;

class Chunk
{
public:
	constexpr static int Height = 3;

private:
	std::vector<std::unique_ptr<ChunkSegment>> _segments;
	coords::ChunkPos _chunkPos{ 0 };

public:
	Chunk(World& world, const coords::ChunkPos& chunkPos, FastNoise& noise, TextureAtlas& textureAtlas);

	const coords::ChunkPos& getChunkPos() const { return _chunkPos; }

	void addChunkSegment(std::unique_ptr<ChunkSegment>& segment);

	ChunkSegment* getChunkSegment(int posZ);

	void generateMesh(TextureAtlas& textureAtlas);

	void drawChunks(ShaderProgram& shaderProgram);
	void drawGrid(ShaderProgram& shaderProgram);
};
