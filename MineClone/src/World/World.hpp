#pragma once

#include <vector>
#include <memory>

#include "Graphics/Texture.hpp"
#include "TextureAtlas.hpp"

#include "Chunk.hpp"

class World
{
private:
	Texture _texture;
	std::unique_ptr<TextureAtlas> _textureAtlas;

	std::vector<std::unique_ptr<Chunk>> _chunks;

public:
	World();

	void init();

	Chunk* getChunk(const glm::ivec3& pos) const;

	void draw(ShaderProgram& shaderProgram);
};
