#pragma once

#include "ChunkSegment.hpp"

class FastNoise;

class Chunk
{
public:
	constexpr static int Height = 3;

private:
	std::vector<std::unique_ptr<ChunkSegment>> _segments;
	glm::ivec2 _posXZ{ 0 };

public:
	Chunk(World& world, const glm::ivec2& posXZ, FastNoise& noise, TextureAtlas& textureAtlas);

	const glm::ivec2& getPosXZ() const { return _posXZ; }

	ChunkSegment* getChunkSegment(int posZ);

	void generateMesh(TextureAtlas& textureAtlas);

	void drawChunks(ShaderProgram& shaderProgram);
	void drawGrid(ShaderProgram& shaderProgram);
};
