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
	TextureAtlas _textureAtlas;

	ChunkManager _chunkManager;

public:
	World();

	void init();

	Chunk* getChunk(const glm::ivec3& pos) const;

	void removeBlock(const glm::ivec3& pos);
	Block* getBlock(const glm::ivec3& pos) const;

	TextureAtlas& getTextureAtlas() { return _textureAtlas; }
	const TextureAtlas& getTextureAtlas() const { return _textureAtlas; }

	void draw(ShaderProgram& shaderProgram);

public:
	static glm::ivec3 getChunkPos(const glm::ivec3& worldPos);
	static glm::ivec3 getLocalPos(const glm::ivec3& worldPos);
	static glm::ivec3 getWorldPos(const glm::ivec3& localPos, const glm::ivec3& chunkPos);
};
