#pragma once

#include <vector>
#include <memory>

#include "Graphics/Texture.hpp"
#include "TextureAtlas.hpp"

#include "ChunkManager.hpp"

class World
{
private:
	Texture _texture;
	std::unique_ptr<TextureAtlas> _textureAtlas;

	ChunkManager _chunkManager;

public:
	World();

	void init();

	Chunk* getChunk(const glm::ivec3& pos) const;

	void draw(ShaderProgram& shaderProgram);
};
